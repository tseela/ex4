#pragma once

#include "MatrixGraphSolution.hpp"
#include "BestPath.hpp"
#include <queue>

namespace solver {

namespace solution {

namespace graph_solution {

class BFS : public solver::solution::MatrixGraphSolution {
public:
    BFS();

    std::string getCacheString() const override;

private:
    std::string algorithm(const graph::Graph& graph) const override;
};

}

}

}