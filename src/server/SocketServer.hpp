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
            SocketServer();
        
            virtual void start(int port, const std::shared_ptr<ClientHandler> ch) override;
            virtual void acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) = 0;

            virtual ~SocketServer() = default;
    };
}