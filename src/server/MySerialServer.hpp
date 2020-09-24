#pragma once

#include "SocketServer.hpp"
#include "SocketIStream.hpp"
#include "SocketOStream.hpp"

#include <atomic>
#include <exception>
#include <pthread.h>
#include <mutex>
#include <thread>
#include <iostream>


namespace server_side {
    
    class MySerialServer: public SocketServer{
        std::atomic_bool m_accepting;
        std::exception_ptr m_tExp = nullptr;
        std::thread m_tAccept;
        std::mutex m_mut;

        public:
            /**
            * @brief Construct a new My Serial Server object.
            * 
            */
            MySerialServer();
            virtual void acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) override;
            

        private:
            /**
             * @brief this function accepting clients.
             * 
             * @param sockfd of the server.
             * @param ch the ClientHandler.
            */
            void threadAccept(int sockfd, const std::shared_ptr<ClientHandler> ch);

            /**
             * @brief this function tells when to stop the server.
             * 
             */
            void stop();
    };
}