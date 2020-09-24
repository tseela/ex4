#pragma once

#include "MatrixGraphSolution.hpp"
#include "DFS.hpp"
#include "BFS.hpp"
#include "AStar.hpp"

namespace solver {

namespace solution {

namespace graph_solution {

class BestFS : public solver::solution::MatrixGraphSolution {
public:
    /**
     * @brief Construct a new BestFS object.
     * 
     */
    BestFS();

    std::string getCacheString() const override;

private:
    std::string algorithm(const graph::Graph& graph) const override;
};

}

}

}