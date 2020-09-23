#pragma once

#include "ClientHandler.hpp"

#include <chrono>
#include <memory>

namespace server_side {
    class Server {
        public:
            static constexpr int SERVER_BACKLOG = 20;
            static constexpr std::chrono::seconds SERVER_TIMEOUT = std::chrono::hours(2);

            virtual void start(int port, const std::shared_ptr<ClientHandler> ch) = 0;
            virtual ~Server() = default;
    };
}