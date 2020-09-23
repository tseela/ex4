#include "GraphProblemHandler.hpp"

#include <iostream>

using namespace std;
using namespace server_side;

void GraphProblemHandler::handleProblem(const std::unique_ptr<SocketIStream> in,
        const std::unique_ptr<SocketOStream> out, std::string alg) const {
                cout<<alg<<endl;
                out->writeOneLine("bay");

                std::string firstLine = in->readOneLine();
                if(firstLine.compare(SocketIStream::STRING_TIMEOUT) == 0) {
                        return; //leave the client
                }
                cout<<firstLine<<endl;

                std::string contant = readFileContent(SocketServer::LOG_LOCATION);
                writeFileContent(SocketServer::LOG_LOCATION, contant + "Task complited, Client was disconnected");
     }