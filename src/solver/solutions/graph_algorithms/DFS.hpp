#pragma once

#include "MatrixGraphSolution.hpp"
#include "BestPath.hpp"

namespace solver {

namespace solution {

namespace graph_solution {

class DFS : public solver::solution::MatrixGraphSolution {
public:
    /**
     * @brief Construct a new DFS object.
     * 
     */
    DFS();

    std::string getCacheString() const override;

private:
    std::string algorithm(const graph::Graph& graph) const override;
};

}

}

}