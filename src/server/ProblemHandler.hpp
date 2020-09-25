#pragma once

#include "SocketIStream.hpp"
#include "SocketOStream.hpp"

#include <string>
#include <memory>

namespace server_side {
    class ProblemHandler {
        public:
            static constexpr auto DEFAULT_ALG = "default";

            static constexpr auto SUCCESS_MASSEGE = "Task complited, Client disconnected\n";

            /**
             * @brief the protocol to handle the problem.
             * 
             * @param in stream to read messages from client.
             * @param out stream to write messages to client.
             * @param alg the alg string.
             */
            virtual void handleProblem(const std::unique_ptr<SocketIStream> in,
                 const std::unique_ptr<SocketOStream> out, std::string alg) const = 0;

            /**
             * @brief Destroy the Problem Handler object.
             * 
             */
            virtual ~ProblemHandler() = default;
    };
}