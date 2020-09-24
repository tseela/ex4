#pragma once

#include "ProblemHandler.hpp"
#include "SocketServer.hpp"

#include <map>
#include <mutex>

namespace server_side {
    class GraphProblemHandler: public ProblemHandler {

        public:
            static constexpr auto GRAPH_DEFAULT_ALG = "DFS";
            virtual void handleProblem(const std::unique_ptr<SocketIStream> in,
                 const std::unique_ptr<SocketOStream> out, std::string alg) const override;
    };
}