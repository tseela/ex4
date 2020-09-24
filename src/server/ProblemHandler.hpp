#pragma once

#include "SocketIStream.hpp"
#include "SocketOStream.hpp"

#include <string>
#include <memory>

namespace server_side {
    class ProblemHandler {
        public:
            static constexpr auto DEFAULT_ALG = "default";

            static constexpr auto SUCCESS_MASSEGE = "Task complited, Client disconnected";

            virtual void handleProblem(const std::unique_ptr<SocketIStream> in,
                 const std::unique_ptr<SocketOStream> out, std::string alg) const = 0;

            virtual ~ProblemHandler() = default;
    };
}