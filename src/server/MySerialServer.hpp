#pragma once

#include "SocketServer.hpp"
#include <atomic>
#include <thread>
 #include <pthread.h>
#include <chrono>
namespace server_side {
    
    class MySerialServer: public SocketServer{
        std::atomic_bool m_accepting;
        std::exception_ptr m_tExp = nullptr;
        std::thread m_tAccept;

        public:
            MySerialServer();
            virtual void acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) override;
            virtual void stop() override;

        private:
            void threadAccept(int sockfd, const std::shared_ptr<ClientHandler> ch);
    };
}