#include <istream>
#include <ostream>

namespace server_side {
    class ClientHandler {
        virtual void handleClient(std::istream in, std::ostream out) const = 0;
    };
};