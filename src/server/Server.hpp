#pragma once

#include "ClientHandler.hpp"

#include <chrono>
#include <memory>

namespace server_side {
    class Server {
        public:
        static constexpr int SERVER_BACKLOG = 5;
        static constexpr std::chrono::seconds SERVER_TIMEOUT = std::chrono::minutes(30);

        virtual void start(int port, const std::shared_ptr<ClientHandler> ch) = 0;
        virtual ~Server() = default;
    };
}