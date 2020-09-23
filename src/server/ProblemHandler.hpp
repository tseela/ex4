#pragma once

#include "SocketIStream.hpp"
#include "SocketOStream.hpp"

#include <string>
#include <memory>

namespace server_side {
    class ProblemHandler {
        public:
            static constexpr std::string_view DEFAULT_ALG = "default";

            virtual void handleProblem(const std::unique_ptr<SocketIStream> in,
                 const std::unique_ptr<SocketOStream> out, std::string alg) const = 0;

            virtual ~ProblemHandler() = default;
    };
}