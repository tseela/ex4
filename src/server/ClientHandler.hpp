#pragma once

#include "SocketIStream.hpp"
#include "SocketOStream.hpp"

#include <memory>

namespace server_side {
    class ClientHandler {
        public:
            virtual void handleClient(std::unique_ptr<SocketIStream> in,
                 std::unique_ptr<SocketOStream> out) const = 0;

            virtual ~ClientHandler() = default;
    };
}