#include <istream>
#include <ostream>

class ClientHandler {
    virtual void handleClient(std::istream in, std::ostream out) = 0;
};