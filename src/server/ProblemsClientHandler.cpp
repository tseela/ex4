#include "ProblemsClientHandler.hpp"

#include <iostream>////////////////////////////////////////////////////////

using namespace server_side;
using namespace std;////////////////////////////////////////////////////////

void ProblemsClientHandler::handleClient(const std::unique_ptr<SocketIStream> in,
     const std::unique_ptr<SocketOStream> out) const {
        cout<<in->readOneLine()<<endl;////////////////////////////////////////////////////////////////////////////////////////////////////
        out->writeOneLine("bay");
     }