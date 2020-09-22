#pragma once

#include "Server.hpp"

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
        
            virtual void start(int port, const std::shared_ptr<ClientHandler> ch) override;
            virtual void acceptClients(int sockfd, const std::shared_ptr<ClientHandler> ch) = 0;

            virtual ~SocketServer() = default;
    };
}