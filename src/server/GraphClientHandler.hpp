#pragma once

#include "ProblemsClientHandler.hpp"

namespace server_side {
    class GraphClientHandler: public ProblemsClientHandler {
        public:
            virtual void handleClient(const std::unique_ptr<SocketIStream> in,
                 const std::unique_ptr<SocketOStream> out) const override;
    };
}