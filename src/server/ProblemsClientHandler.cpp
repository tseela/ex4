#include "ProblemsClientHandler.hpp"

#define NOT_ENOUGH_ARGUMENS std::runtime_error("Expecting more arguments")
#define NOT_SUPPORT_PROBLEM std::runtime_error("The problem given isn't supported")
using namespace server_side;

ProblemsClientHandler::ProblemsClientHandler() {
        m_problems = std::map<std::string, std::shared_ptr<ProblemHandler>>();
}

void ProblemsClientHandler::handleClient(std::unique_ptr<SocketIStream> in,
     std::unique_ptr<SocketOStream> out) const {
        std::string firstLine = in->readOneLine();
        if(firstLine.compare(SocketIStream::STRING_TIMEOUT) == 0) {
                return; //leave the client
        }

        auto problemStartIndex = firstLine.find_first_of(SPACE);
        if(problemStartIndex == std::string::npos) {
                throw NOT_ENOUGH_ARGUMENS;
        }

        std::string problemString = firstLine.substr(problemStartIndex);

        problemStartIndex = problemString.find_first_not_of(SPACE);
        if(problemStartIndex == std::string::npos) {
                throw NOT_ENOUGH_ARGUMENS;
        }

        problemString = problemString.substr(problemStartIndex);

        std::string algString;
        auto problemEndIndex = problemString.find_first_of(SPACE);
        if(problemEndIndex == std::string::npos) {
                algString = ProblemHandler::DEFAULT_ALG;
        } else {
                algString = problemString.substr(problemEndIndex);
                algString.erase(remove_if(algString.begin(), algString.end(), isspace), algString.end());

                problemString = problemString.substr(0, problemEndIndex);    
        }

        std::lock_guard<std::mutex> guard(m_lockMap);

        auto pair = m_problems.find(problemString);
        if(pair == m_problems.end()) {
                throw NOT_SUPPORT_PROBLEM;
        }

        std::shared_ptr<ProblemHandler> problem = pair->second;

        problem->handleProblem(std::move(in), std::move(out), std::move(algString));
     }

        void ProblemsClientHandler::addProblemHandler(std::string problemString,
                std::shared_ptr<ProblemHandler> problem){

                        std::lock_guard<std::mutex> guard(m_lockMap);

                        m_problems.insert(std::pair<std::string,
                                std::shared_ptr<ProblemHandler>>(problemString, problem));
                }