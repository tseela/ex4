#pragma once

#include "Server.hpp"
#include "file_reading.hpp"

#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <system_error>
#include <chrono>

namespace server_side {
    class SocketServer: public Server{ 

        public:
            static constexpr auto LOG_LOCATION = "SERVER_LOG.txt";
            static constexpr auto LOG_TITLE ="Welcome to the server log file!\n";

            static constexpr auto ACCEPTE_MASSEGE_TO_LOG = "New client was accepted!\n";
            static constexpr auto FAILED_MASSEGE_TO_LOG = "Task Failed, Client disconnected with this exception: ";
            static constexpr auto WRITING_MASSEGE_TO_LOG_FAILED = "Couldn't write to server log file that was an exception in client";
            SocketServer();
        
            virtual void start(int port, const std::shared_ptr<ClientHandler> ch) override;
            virtual void acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) = 0;

            virtual ~SocketServer() = default;
    };
}