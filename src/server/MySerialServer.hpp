#include "Server.hpp"

namespace server_side {
    class MySerialServer: public Server{
        virtual void open(int port, ClientHandler ch);
        virtual void stop();
    };
};