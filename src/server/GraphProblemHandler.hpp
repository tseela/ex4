#pragma once

#include "SocketServer.hpp"
#include "ProblemHandler.hpp"
#include "Solver.hpp"
#include "MatrixGraphProblem.hpp"
#include "MatrixGraphSolution.hpp"
#include "AStar.hpp"
#include "BestFS.hpp"
#include "BFS.hpp"
#include "DFS.hpp"

#include <string>
#include <algorithm>
#include <cstddef>
#include <vector>

namespace server_side {
    class GraphProblemHandler: public ProblemHandler {
        public:
            static constexpr auto CLIENT_BORDER = "b";
            static constexpr auto GRAPH_DEFAULT_ALG = "BestFS";

            virtual void handleProblem(std::unique_ptr<SocketIStream> in,
                std::unique_ptr<SocketOStream> out, std::string alg) const override;
        private:
            /**
             * @brief Get the Solution thats sute to the alguritem.
             * 
             * @param out out stream to the client.
             * @param alg the alg name.
             * @return std::unique_ptr<solver::solution::MatrixGraphSolution> the solution with the alg.
             */
            std::unique_ptr<solver::solution::MatrixGraphSolution> getSolution(
                SocketOStream* out, std::string alg) const;

            /**
             * @brief Get the Matix Raw.
             * 
             * @param in in stream to the client.
             * @param out out stream to the client.
             * @param matrix the mtrix to put in the raw that was read.
             * @param rowIndex the row index.
             */
            void getMatixRaw(SocketIStream* in, SocketOStream* out,
                 matrix::MatrixClass* matrix, std::uint32_t rowIndex) const;

            /**
             * @brief Get the Two Value Raw object.
             * for parsing the rows that shoul only be: int,int
             * 
             * @param in in stream to the client.
             * @param out out stream to the client.
             * @return std::vector<std::uint32_t> the vector with the values in the row.
             */
            std::vector<std::uint32_t> getTwoValueRaw(SocketIStream* in, SocketOStream* out) const;
    };
}