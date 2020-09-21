#pragma once

#include <istream>
#include <ostream>

namespace server_side {
    class ClientHandler { //needs rule of 5 because smart pointer?????
        ClientHandler(const ClientHandler& ClientHandler);
        ClientHandler& operator=(const ClientHandler& source);
        virtual void handleClient(std::istream in, std::ostream out) const = 0;
        virtual ~ClientHandler() = default;
    };
}