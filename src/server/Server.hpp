#include "ClientHandler.hpp"

#include <memory>
namespace server_side {
    class Server {
        virtual void open(int port, const std::shared_ptr<ClientHandler> ch) const = 0;
        virtual void stop() = 0;
    };
};