#include "MyParallelServer.hpp"

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

using namespace server_side;
using namespace std::chrono;

MyParallelServer::MyParallelServer() : m_accepting(false), m_terminatePool(false) {}

void MyParallelServer::acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) {
    m_tAccept = std::thread(&MyParallelServer::threadAccept, this, sockfd);

    for(int i = 0; i < NUM_ACCEPTING_THREADS; ++i) {
        m_threadPool.push_back(std::thread(&MyParallelServer::oneThreadAccept,
                     this, ch));
    }

    stop(); //detroys also the thread
}

void MyParallelServer::threadAccept(int sockfd) {
    while(true) {
        try{
            sockaddr_in cliAddr;
            socklen_t cliLen = sizeof(cliAddr);
            const auto cliSockfd = accept(sockfd,  reinterpret_cast<sockaddr*>(&cliAddr), &cliLen);
            if(cliSockfd < 0) {
                THROW_SYSTEM_ERROR(); 
            }

            std::unique_lock<std::mutex> lock(m_mutCliVec);
            
            std::string contant = readFileContent(SocketServer::LOG_LOCATION);
            writeFileContent(SocketServer::LOG_LOCATION, contant + "New client was accepted!\n");

            m_cliSocketfd.push(cliSockfd);

            lock.unlock();

            m_acceptingCV.notify_one();
        } catch (const std::exception& e) {
            std::cerr<<e.what()<<std::endl;
        }
    }

}

void MyParallelServer::oneThreadAccept(const std::shared_ptr<ClientHandler> ch) {
    while(true) {
        int cliSockfd;
        try{

            std::unique_lock<std::mutex> lock(m_mutCliVec);

            m_acceptingCV.wait(lock, [this]{return !m_cliSocketfd.empty() || m_terminatePool;});

            if(m_terminatePool) {
                break;
            }

            cliSockfd = m_cliSocketfd.front();

            m_cliSocketfd.pop();

            m_accepting = true;
            
            lock.unlock();

            std::unique_ptr<SocketIStream> in = std::make_unique<SocketIStream>(cliSockfd);
            std::unique_ptr<SocketOStream> out = std::make_unique<SocketOStream>(cliSockfd);
            ch->handleClient(std::move(in), std::move(out));

            close(cliSockfd);

            std::unique_lock<std::mutex> lockAgain(m_mutCliVec);
            if(m_cliSocketfd.empty()) {
                 m_accepting = false;
                 m_stoppingCV.notify_all();
            }
        } catch (const std::exception& e) {
            std::string error = e.what();
            if (write(cliSockfd, error.data(), error.size()) < 0) {
                std::cerr<<"Couldn't write to client this exceptoin:"<<e.what()<<std::endl;
            }
            close(cliSockfd);
        }
    }

}

void MyParallelServer::stop() {
    do {
        if(m_accepting) {
            std::unique_lock<std::mutex> lock(m_mutCliVec);
            m_stoppingCV.wait(lock, [this]{return !m_accepting;});
        }

        if(!m_accepting) {
            std::this_thread::sleep_for(SERVER_TIMEOUT);
        } 

    } while (m_accepting);

    if (0 != pthread_cancel(m_tAccept.native_handle())) {
            THROW_SYSTEM_ERROR(); 
    }
    m_tAccept.join();


    m_terminatePool = true;

    m_acceptingCV.notify_all();

    for(std::thread &oneThread : m_threadPool) {
        oneThread.join();
    }

    m_threadPool.clear();  
}    