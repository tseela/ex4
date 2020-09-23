#pragma once

#include "MatrixGraphSolution.hpp"

struct BestPath {
    double bestCost;
    std::string bestPath;

    void initialFields(const graph::Graph& graph);
};

namespace solver {

namespace solution {

class DFS : public solver::solution::MatrixGraphSolution {
public:
    DFS();

    std::string getCacheString() const override;

private:
    std::string algorithm(const graph::Graph& graph) const override;
};

}

}