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

            /**
             * @brief Construct a new Problems Client Handler object.
             * 
             */
            ProblemsClientHandler();

            virtual void handleClient(std::unique_ptr<SocketIStream> in,
                 std::unique_ptr<SocketOStream> out) const override;

            /**
             * @brief Adding problem handeler so the server would support it.
             * 
             * @param problemString the problem name.
             * @param problem the ProblemHandler.
             */
            void addProblemHandler(std::string problemString,
                std::shared_ptr<ProblemHandler> problem);
    };
}