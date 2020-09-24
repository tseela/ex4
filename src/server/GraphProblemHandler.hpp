#pragma once

#include "SocketServer.hpp"
#include "ProblemHandler.hpp"
#include "MatrixGraphProblem.hpp"
#include "MatrixGraphSolution.hpp"
#include "AStar.hpp"
#include "BestFS.hpp"
#include "BFS.hpp"
#include "DFS.hpp"

#include <string>
#include <algorithm>
#include <cstddef>

namespace server_side {
    class GraphProblemHandler: public ProblemHandler {
        public:
            static constexpr auto CLIENT_BORDER = "b";
            static constexpr auto GRAPH_DEFAULT_ALG = "BestFS";

            virtual void handleProblem(std::unique_ptr<SocketIStream> in,
                std::unique_ptr<SocketOStream> out, std::string alg) const override;
        private:
            std::unique_ptr<solver::solution::MatrixGraphSolution> getSolution(
                SocketOStream* out, std::string alg) const;

            void getMatixRaw(SocketIStream* in, SocketOStream* out,
                 matrix::MatrixClass* matrix, std::uint32_t rowIndex) const;
    };
}