#include "MySerialServer.hpp"

#include <iostream>////////////////////////////////////////////////////////

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

using namespace server_side;
using namespace std::chrono;
using namespace std;////////////////////////////////////////////////////////

MySerialServer::MySerialServer() : m_accepting(false){}

void MySerialServer::acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) {
    try{
        m_tAccept = std::thread(&MySerialServer::threadAccept, this, sockfd, ch);
        stop(); //detroys also the thread
        cout<<"dead"<<endl;////////////////////////////////////////////////////////////////////////////////////////////////////

        if (m_tExp) {
            std::rethrow_exception(m_tExp);
        }
    } catch (const std::exception& e) {
        close(sockfd);
        throw e;
    }
}

void MySerialServer::threadAccept(int sockfd, const std::shared_ptr<ClientHandler> ch) {
    if (ch == NULL){}/////////////////////////////////////////////////////////////////////////////////////////////////////////

    try{
        while(1) {

            sockaddr_in cliAddr;
            socklen_t cliLen = sizeof(cliAddr);
            if(0 > accept(sockfd,  reinterpret_cast<sockaddr*>(&cliAddr), &cliLen)) {
                THROW_SYSTEM_ERROR(); 
            }

            m_accepting = true;

        }
    } catch (const std::exception& e) {
        m_tExp = std::current_exception();
    }
}

void MySerialServer::stop() {
    do {
        m_accepting = false;
        std::this_thread::sleep_for(5s);

    } while (m_accepting);

    if (0 != pthread_cancel(m_tAccept.native_handle())) {
            THROW_SYSTEM_ERROR(); 
    }
    
    m_tAccept.join();
}