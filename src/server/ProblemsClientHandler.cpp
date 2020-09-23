#include "ProblemsClientHandler.hpp"

using namespace server_side;

void ProblemsClientHandler::handleClient(const std::unique_ptr<SocketIStream> in,
     const std::unique_ptr<SocketOStream> out) const {
        std::string firstLine = in->readOneLine();

        auto problemStartIndex = firstLine.find_first_of(" ");
        if(problemStartIndex == std::string::npos) {
                throw std::runtime_error("Expecting more argumenting");
        }

        std::string problemString = firstLine.substr(problemStartIndex);

        problemStartIndex = problemString.find_first_not_of(" ");
        if(problemStartIndex == std::string::npos) {
                throw std::runtime_error("Expecting more argumenting");
        }

        problemString = problemString.substr(problemStartIndex);

        auto problemEndIndex = problemString.find_first_of(" ");
        if(problemEndIndex == std::string::npos) {
                throw std::runtime_error("Expecting more argumenting");
        }

        std::string algString = problemString.substr(problemEndIndex);
        algString.erase(remove_if(algString.begin(), algString.end(), isspace), algString.end());

        problemString = problemString.substr(0, problemEndIndex);
     }