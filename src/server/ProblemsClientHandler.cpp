#include "ProblemsClientHandler.hpp"

#define NOT_ENOUGH_ARGUMENS throw std::runtime_error("Expecting more arguments")
#define NOT_SUPPORT_PROBLEM throw std::runtime_error("The given problem isn't supported")
using namespace server_side;

ProblemsClientHandler::ProblemsClientHandler() {
        m_problems = std::map<std::string, std::shared_ptr<ProblemHandler>>();
}

void ProblemsClientHandler::handleClient(std::unique_ptr<SocketIStream> in,
     std::unique_ptr<SocketOStream> out) const {
        //riding the first messege
        std::string firstLine = in->readOneMassege();
        //gets the problem string & the alg string
        auto problemStartIndex = firstLine.find_first_of(SPACE);
        if(problemStartIndex == std::string::npos) {
                out->writeOneMassege(SocketOStream::NO_RESPONSE, SocketOStream::NOT_ENOUGH_ARG);
                NOT_ENOUGH_ARGUMENS;
        }

        //deleting the "solce" word
        std::string problemString = firstLine.substr(problemStartIndex);

        problemStartIndex = problemString.find_first_not_of(SPACE);
        if(problemStartIndex == std::string::npos) {
                out->writeOneMassege(SocketOStream::NO_RESPONSE, SocketOStream::NOT_ENOUGH_ARG);
                NOT_ENOUGH_ARGUMENS;
        }
        //deleting start spaces
        problemString = problemString.substr(problemStartIndex);

        std::string algString;
        auto problemEndIndex = problemString.find_first_of(SPACE);
        if(problemEndIndex == std::string::npos) { //if alg wasn't sended (default alg)
                problemString.erase(remove_if(problemString.begin(),
                        problemString.end(), ::isspace), problemString.end());
                algString = ProblemHandler::DEFAULT_ALG;
        } else {//if the alg was sended
                algString = problemString.substr(problemEndIndex);
                algString.erase(remove_if(algString.begin(), algString.end(), ::isspace), algString.end());

                problemString = problemString.substr(0, problemEndIndex);    
        }

        std::unique_lock<std::mutex> lock(m_lockMap);

        //searching the problem in the map
        auto pair = m_problems.find(problemString);
        if(pair == m_problems.end()) {
                out->writeOneMassege(SocketOStream::NO_RESPONSE, SocketOStream::NOT_SUPPORTED_PROBLEM);
                NOT_SUPPORT_PROBLEM;
        }

        lock.unlock();

        std::shared_ptr<ProblemHandler> problem = pair->second;

        out->writeOneMassege(SocketOStream::NO_RESPONSE);
        problem->handleProblem(std::move(in), std::move(out), std::move(algString));

        //wirting to log server file -success
        std::string contant = files::readFileContent(SocketServer::LOG_LOCATION);
        files::writeFileContent(SocketServer::LOG_LOCATION, contant + ProblemHandler::SUCCESS_MASSEGE);
     }

        void ProblemsClientHandler::addProblemHandler(std::string problemString,
                std::shared_ptr<ProblemHandler> problem){

                        std::unique_lock<std::mutex> lock(m_lockMap);

                        m_problems.insert(std::pair<std::string,
                                std::shared_ptr<ProblemHandler>>(problemString, problem));
                }