#include "MyParallelServer.hpp"

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

using namespace server_side;
using namespace std::chrono;

MyParallelServer::MyParallelServer() : m_accepting(false), m_terminatePool(false) {}

void MyParallelServer::acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) {
    //strting to accept clients
    m_tAccept = std::thread(&MyParallelServer::threadAccept, this, sockfd);

    //creating threads to handle the clients
    for(int i = 0; i < NUM_ACCEPTING_THREADS; ++i) {
        m_threadPool.push_back(std::thread(&MyParallelServer::oneThreadAccept,
                     this, ch));
    }

    stop(); //detroys also the thread
}

void MyParallelServer::threadAccept(int sockfd) {
    while(true) {
        try{
            //wating to accept client
            sockaddr_in cliAddr;
            socklen_t cliLen = sizeof(cliAddr);
            const auto cliSockfd = accept(sockfd,  reinterpret_cast<sockaddr*>(&cliAddr), &cliLen);
            if(cliSockfd < 0) {
                THROW_SYSTEM_ERROR(); 
            }

            //adding the client to the accept client queue
            std::unique_lock<std::mutex> lock(m_mutCliVec);

            std::string contant = files::readFileContent(SocketServer::LOG_LOCATION);
            files::writeFileContent(SocketServer::LOG_LOCATION, contant + ACCEPTE_MASSEGE_TO_LOG);

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
            //waiting to handle client
            std::unique_lock<std::mutex> lock(m_mutCliVec);

            m_acceptingCV.wait(lock, [this]{return !m_cliSocketfd.empty() || m_terminatePool;});

            //if we stopped those threads.
            if(m_terminatePool) {
                break;
            }

            //gets the client to handle
            cliSockfd = m_cliSocketfd.front();

            m_cliSocketfd.pop();

            m_accepting = true;
            
            lock.unlock();

            //handeling the client
            std::unique_ptr<SocketIStream> in = std::make_unique<SocketIStream>(cliSockfd);
            std::unique_ptr<SocketOStream> out = std::make_unique<SocketOStream>(cliSockfd);
            ch->handleClient(std::move(in), std::move(out));
            close(cliSockfd);

            //if no more clients start timeout
            std::unique_lock<std::mutex> lockAgain(m_mutCliVec);
            if(m_cliSocketfd.empty()) {
                 m_accepting = false;
                 m_stoppingCV.notify_all();
            }
        } catch (const std::exception& e) {
            std::string error = e.what();

            try{//writing to the log server
                std::string contant = files::readFileContent(SocketServer::LOG_LOCATION);
                files::writeFileContent(SocketServer::LOG_LOCATION,
                contant + FAILED_MASSEGE_TO_LOG + error);
            } catch (const std::exception& eLog) {
                std::cerr<<WRITING_MASSEGE_TO_LOG_FAILED<<std::endl;
            }

            close(cliSockfd);
        }
    }

}

void MyParallelServer::stop() {
    do {
        if(m_accepting) {//waiting to start timeout
            std::unique_lock<std::mutex> lock(m_mutCliVec);
            m_stoppingCV.wait(lock, [this]{return !m_accepting;});
        }

        //starting the timeout
        if(!m_accepting) {
            std::this_thread::sleep_for(SERVER_TIMEOUT);
        } 

    } while (m_accepting);

    //stop the accepting client
    if (0 != pthread_cancel(m_tAccept.native_handle())) {
            THROW_SYSTEM_ERROR(); 
    }
    m_tAccept.join();

    //stops the handle clients
    m_terminatePool = true;

    m_acceptingCV.notify_all();

    for(std::thread &oneThread : m_threadPool) {
        oneThread.join();
    }

    m_threadPool.clear();  
}    