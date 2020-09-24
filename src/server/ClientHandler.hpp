#pragma once

#include "SocketIStream.hpp"
#include "SocketOStream.hpp"

#include <memory>

namespace server_side {
    class ClientHandler {
        public:
            /**
             * @brief Handels the client.
             * 
             * @param in the input stream.
             * @param out the output stream.
             */
            virtual void handleClient(std::unique_ptr<SocketIStream> in,
                 std::unique_ptr<SocketOStream> out) const = 0;

            /**
             * @brief Destroy the Client Handler object.
             * 
             */
            virtual ~ClientHandler() = default;
    };
}