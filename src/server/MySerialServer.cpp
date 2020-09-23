#include "MySerialServer.hpp"

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

using namespace server_side;
using namespace std::chrono;

MySerialServer::MySerialServer() : m_accepting(false){}

void MySerialServer::acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) {
    try{
        m_tAccept = std::thread(&MySerialServer::threadAccept, this, sockfd, ch);
        stop(); //detroys also the thread

        if (m_tExp) {
            std::rethrow_exception(m_tExp);
        }
    } catch (const std::exception& e) {
        m_tAccept.join();
        close(sockfd);
        throw e;
    }
}

void MySerialServer::threadAccept(int sockfd, const std::shared_ptr<ClientHandler> ch) {
    while(true) {
        int cliSockfd;
        try{
            m_accepting = false;
            sockaddr_in cliAddr;
            socklen_t cliLen = sizeof(cliAddr);
            cliSockfd = accept(sockfd,  reinterpret_cast<sockaddr*>(&cliAddr), &cliLen);
            if(cliSockfd < 0) {
                THROW_SYSTEM_ERROR(); 
            }

            std::lock_guard<std::mutex> guard(m_mut);

            std::string contant = readFileContent(SocketServer::LOG_LOCATION);
            writeFileContent(SocketServer::LOG_LOCATION, contant + "New client was accepted!\n");

            m_accepting = true;

            std::unique_ptr<SocketIStream> in = std::make_unique<SocketIStream>(cliSockfd);
            std::unique_ptr<SocketOStream> out = std::make_unique<SocketOStream>(cliSockfd);
            ch->handleClient(std::move(in), std::move(out));
            close(cliSockfd);
        } catch (const std::exception& e) {
            if(m_accepting) {
                std::string error = e.what();
                try{
                    std::string contant = readFileContent(SocketServer::LOG_LOCATION);
                    writeFileContent(SocketServer::LOG_LOCATION,
                     contant + "Task Failed, Client disconnected with this exception: " + error);
                } catch (const std::exception& eLog) {
                    std::cerr<<"Couldn't write to server log file that was an exception in client"<<std::endl;
                }
                if (write(cliSockfd, error.data(), error.size()) < 0) {
                    std::cerr<<"Couldn't write to client this exception:"<<e.what()<<std::endl;
                }
                close(cliSockfd);
            } else {
                std::cerr<<e.what()<<std::endl;
            }
        }
    }
}

void MySerialServer::stop() {
    do {
        if(m_accepting) {
            std::lock_guard<std::mutex> guard(m_mut);
        }

        if(!m_accepting) {
            std::this_thread::sleep_for(SERVER_TIMEOUT);
        } 
        
    } while (m_accepting);

    if (0 != pthread_cancel(m_tAccept.native_handle())) {
            THROW_SYSTEM_ERROR(); 
    }

    m_tAccept.join();
}