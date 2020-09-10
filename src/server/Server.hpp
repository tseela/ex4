#include "ClientHandler.hpp"
namespace side_server {
    class Server {
        virtual void open(int port, ClientHandler ch) = 0;
        virtual void stop() = 0;
    };
};