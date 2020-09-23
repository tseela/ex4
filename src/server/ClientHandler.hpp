#pragma once

#include "SocketIStream.hpp"
#include "SocketOStream.hpp"

#include <memory>

namespace server_side {
    class ClientHandler {
        public:
            virtual void handleClient(const std::unique_ptr<SocketIStream> in,
                 const std::unique_ptr<SocketOStream> out) const = 0;

            virtual ~ClientHandler() = default;
    };
}