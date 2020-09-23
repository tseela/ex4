#pragma once

#include "ProblemHandler.hpp"

namespace server_side {
    class GraphProblemHandler: public ProblemHandler {
        public:
            virtual void handleProblem(const std::unique_ptr<SocketIStream> in,
                 const std::unique_ptr<SocketOStream> out, std::string alg) const override;
    };
}