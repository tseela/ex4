#pragma once

#include "ClientHandler.hpp"

namespace server_side {
    class MyTestClientHandler: public ClientHandler {
        virtual void handleClient(std::istream in, std::ostream out) const override;
    };
};