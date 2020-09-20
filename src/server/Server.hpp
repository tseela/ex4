#include "ClientHandler.hpp"
namespace server_side {
    class Server {
        virtual void open(int port, ClientHandler ch) = 0;
        virtual void stop() = 0;
    };
};