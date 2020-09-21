#include "Server.hpp"

#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <system_error>

namespace server_side {
    class SocketServer: public Server{
        protected:
        bool m_stop;
        
        public:
        SocketServer();
        virtual void open(int port, const std::shared_ptr<ClientHandler> ch) const override;
        virtual void stop() override;
        virtual void acceptClients() const = 0;
    };
};