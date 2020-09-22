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
    try{
        while(1) {
            m_accepting = false;
            sockaddr_in cliAddr;
            socklen_t cliLen = sizeof(cliAddr);
            const auto cliSockfd = accept(sockfd,  reinterpret_cast<sockaddr*>(&cliAddr), &cliLen);
            if(cliSockfd < 0) {
                THROW_SYSTEM_ERROR(); 
            }

            std::lock_guard<std::mutex> guard(m_mut);

            m_accepting = true;

            std::unique_ptr<SocketIStream> in = std::make_unique<SocketIStream>(cliSockfd);
            std::unique_ptr<SocketOStream> out = std::make_unique<SocketOStream>(cliSockfd);
            ch->handleClient(std::move(in), std::move(out));

        }
    } catch (const std::exception& e) {
        m_tExp = std::current_exception();
        m_accepting = false;
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