#pragma once

#include "ClientHandler.hpp"

#include <string>
#include <algorithm>

namespace server_side {
    class ProblemsClientHandler: public ClientHandler {
        public:
            virtual void handleClient(const std::unique_ptr<SocketIStream> in,
                 const std::unique_ptr<SocketOStream> out) const override;
    };
}