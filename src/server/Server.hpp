#pragma once

#include "ClientHandler.hpp"

#include <chrono>
#include <memory>

namespace server_side {
    class Server {
        public:
            static constexpr auto SERVER_BACKLOG = 20;
            static constexpr std::chrono::seconds SERVER_TIMEOUT = std::chrono::hours(2);

            /**
             * @brief starts the server and would stop when the SERVER_TIMEOUT pased.
             * 
             * @param port the port to bind.
             * @param ch the clinet handeler.
             */
            virtual void start(int port, const std::shared_ptr<ClientHandler> ch) = 0;

            /**
             * @brief Destroy the Server object.
             * 
             */
            virtual ~Server() = default;
    };
}