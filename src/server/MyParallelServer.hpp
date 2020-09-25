#pragma once

#include "SocketServer.hpp"
#include "SocketIStream.hpp"
#include "SocketOStream.hpp"

#include <atomic>
#include <exception>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>
#include <pthread.h>
#include <condition_variable>
#include <iostream>

namespace server_side {
    class MyParallelServer: public SocketServer{
        std::atomic_bool m_accepting;
        std::atomic_bool m_terminatePool;
        std::exception_ptr m_tExp = nullptr;
        std::vector<std::thread> m_threadPool;
        std::queue<int> m_cliSocketfd;
        std::thread m_tAccept;
        std::mutex m_mutCliVec;
        std::condition_variable m_acceptingCV;
        std::condition_variable m_stoppingCV;
        

        public:
            static constexpr auto NUM_ACCEPTING_THREADS = 10;

            /**
             * @brief Construct a new My Parallel Server object.
             * 
             */
            MyParallelServer();


            virtual void acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) override;
            

        private:
            /**
             * @brief this thread-func is accepting clients.
             * 
             * @param sockfd of the server.
             */
            void threadAccept(int sockfd);

            /**
             * @brief this thried-func is to handle the clients.
             * 
             * @param ch the ClientHandler.
             */
            void oneThreadAccept(const std::shared_ptr<ClientHandler> ch);

            /**
             * @brief this function tells when to stop the server.
             * 
             */
            void stop();
    };
}