#pragma once

#include "ClientHandler.hpp"
#include "ProblemHandler.hpp"

#include <string>
#include <algorithm>
#include <map>
#include <mutex>
#include <cstddef>

namespace server_side {
    class ProblemsClientHandler: public ClientHandler {
        
        mutable std::mutex m_lockMap;
        std::map<std::string, std::shared_ptr<ProblemHandler>> m_problems;
    
        public:
            static constexpr auto SPACE = " ";
            static constexpr auto REQUIRED_BREAKS = 2;

            ProblemsClientHandler();

            virtual void handleClient(std::unique_ptr<SocketIStream> in,
                 std::unique_ptr<SocketOStream> out) const override;

            void addProblemHandler(std::string problemString,
                std::shared_ptr<ProblemHandler> problem);
    };
}