#pragma once

#include "SocketIStream.hpp"
#include "SocketOStream.hpp"

#include <istream>
#include <ostream>
#include <memory>

namespace server_side {
    class ClientHandler { //needs rule of 5 because smart pointer?????
        public:
            ClientHandler(const ClientHandler& ClientHandler);

            ClientHandler& operator=(const ClientHandler& source);

            virtual void handleClient(const std::unique_ptr<SocketIStream> in,
                 const std::unique_ptr<SocketOStream> out) const = 0;

            virtual ~ClientHandler() = default;
    };
}