#include "ProblemsClientHandler.hpp"

#define NOT_ENOUGH_ARGUMENS std::runtime_error("Expecting more arguments")
#define NOT_SUPPORT_PROBLEM std::runtime_error("The given problem isn't supported")
#define START_BREAKS_ERROR std::runtime_error("Expecting 2 break lines after first messege")
using namespace server_side;

ProblemsClientHandler::ProblemsClientHandler() {
        m_problems = std::map<std::string, std::shared_ptr<ProblemHandler>>();
}

void ProblemsClientHandler::handleClient(std::unique_ptr<SocketIStream> in,
     std::unique_ptr<SocketOStream> out) const {
        int numOfBreakLine = 0;
        std::string firstLine = in->readOneMassege();

        std::string checksBreakLines = firstLine;
        while(numOfBreakLine != REQUIRED_BREAKS) {
                std::size_t found = checksBreakLines.rfind(SocketOStream::BREAK_LINE);
                if (found != std::string::npos) {
                        //deleting the found break
                        checksBreakLines.replace(found, SocketOStream::BREAK_LINE_SIZE, "");
                        ++numOfBreakLine;
                        continue;
                }

                checksBreakLines = in->readOneMassege();
                std::string chekNotImportedMassege = checksBreakLines;
                checksBreakLines.erase(remove_if(checksBreakLines.begin(),
                         checksBreakLines.end(), isspace), checksBreakLines.end());
                if(checksBreakLines.size() != 0) {
                        out->writeOneMassege(SocketOStream::NO_RESPONSE, SocketOStream::NO_START_BREAKS);
                        throw START_BREAKS_ERROR;
                }
        }

        if(firstLine.compare(SocketIStream::STRING_TIMEOUT) == 0) {
                return; //leave the client
        }

        auto problemStartIndex = firstLine.find_first_of(SPACE);
        if(problemStartIndex == std::string::npos) {
                out->writeOneMassege(SocketOStream::NO_RESPONSE, SocketOStream::NOT_ENOUGH_ARG);
                throw NOT_ENOUGH_ARGUMENS;
        }

        std::string problemString = firstLine.substr(problemStartIndex);

        problemStartIndex = problemString.find_first_not_of(SPACE);
        if(problemStartIndex == std::string::npos) {
                out->writeOneMassege(SocketOStream::NO_RESPONSE, SocketOStream::NOT_ENOUGH_ARG);
                throw NOT_ENOUGH_ARGUMENS;
        }

        problemString = problemString.substr(problemStartIndex);

        std::string algString;
        auto problemEndIndex = problemString.find_first_of(SPACE);
        if(problemEndIndex == std::string::npos) {
                problemString.erase(remove_if(problemString.begin(),
                        problemString.end(), isspace), problemString.end());
                algString = ProblemHandler::DEFAULT_ALG;
        } else {
                algString = problemString.substr(problemEndIndex);
                algString.erase(remove_if(algString.begin(), algString.end(), isspace), algString.end());

                problemString = problemString.substr(0, problemEndIndex);    
        }

        std::unique_lock<std::mutex> lock(m_lockMap);

        auto pair = m_problems.find(problemString);
        if(pair == m_problems.end()) {
                out->writeOneMassege(SocketOStream::NO_RESPONSE, SocketOStream::NOT_SUPPORTED_PROBLEM);
                throw NOT_SUPPORT_PROBLEM;
        }

        lock.unlock();

        std::shared_ptr<ProblemHandler> problem = pair->second;

        out->writeOneMassege(SocketOStream::NO_RESPONSE);
        problem->handleProblem(std::move(in), std::move(out), std::move(algString));
     }

        void ProblemsClientHandler::addProblemHandler(std::string problemString,
                std::shared_ptr<ProblemHandler> problem){

                        std::unique_lock<std::mutex> lock(m_lockMap);

                        m_problems.insert(std::pair<std::string,
                                std::shared_ptr<ProblemHandler>>(problemString, problem));
                }