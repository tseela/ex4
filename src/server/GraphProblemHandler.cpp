#include "GraphProblemHandler.hpp"

#include <iostream>

using namespace std;
using namespace server_side;

void GraphProblemHandler::handleProblem(const std::unique_ptr<SocketIStream> in,
        const std::unique_ptr<SocketOStream> out, std::string alg) const {
                if(alg.compare(DEFAULT_ALG) == 0) {
                        alg = GRAPH_DEFAULT_ALG;
                }
                out->writeOneMassege(alg);

                std::string firstLine = in->readOneMassege();
                if(firstLine.compare(SocketIStream::STRING_TIMEOUT) == 0) {
                        return; //leave the client
                }
                cout<<firstLine<<endl;

                //wirting to log server file -success
                std::string contant = files::readFileContent(SocketServer::LOG_LOCATION);
                files::writeFileContent(SocketServer::LOG_LOCATION, contant + SUCCESS_MASSEGE);
     }