#pragma once

#include "ClientHandler.hpp"

#include <memory>
namespace server_side {
    class Server {
        public:
        virtual void open(int port, const std::shared_ptr<ClientHandler> ch) = 0;
        virtual void stop() = 0;
        virtual ~Server() = default;
    };
}