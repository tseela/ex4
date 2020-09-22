#pragma once

#include "ClientHandler.hpp"

namespace server_side {
    class ProblemsClientHandler: public ClientHandler {
            virtual void handleClient(const std::unique_ptr<SocketIStream> in,
                 const std::unique_ptr<SocketOStream> out) const override;
    };
}