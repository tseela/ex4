#pragma once

#include "SocketServer.hpp"
#include "SocketIStream.hpp"
#include "SocketOStream.hpp"

#include <atomic>
#include <exception>
#include <mutex>
#include <thread>
#include <pthread.h>

namespace server_side {
    
    class MySerialServer: public SocketServer{
        std::atomic_bool m_accepting;
        std::exception_ptr m_tExp = nullptr;
        std::thread m_tAccept;
        std::mutex m_mut;

        public:

            MySerialServer();
            virtual void acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) override;
            

        private:
            void threadAccept(int sockfd, const std::shared_ptr<ClientHandler> ch);
            void stop();
    };
}