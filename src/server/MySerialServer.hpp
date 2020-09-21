#include "SocketServer.hpp"

namespace server_side {
    class MySerialServer: public SocketServer{
        bool m_stop;
        
        public:
        virtual void acceptClients() const override;
    };
};