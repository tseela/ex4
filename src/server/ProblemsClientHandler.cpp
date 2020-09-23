#include "ProblemsClientHandler.hpp"

using namespace server_side;

void ProblemsClientHandler::handleClient(const std::unique_ptr<SocketIStream> in,
     const std::unique_ptr<SocketOStream> out) const {
        in->readOneLine();
        out->writeOneLine("bay");
     }