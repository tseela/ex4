#pragma once

#include "MatrixGraphSolution.hpp"
#include "BestPath.hpp"
#include <queue>

struct Step {
    std::uint32_t vertex_x;
    std::uint32_t vertex_y;
    std::string my_path;
    double my_cost;
    matrix::MatrixClass isStepped;

    Step(std::uint32_t x, std::uint32_t y, std::string path, double cost, matrix::MatrixClass isStepped);
    Step(const graph::Graph& graph, Step before, Direction direction);
};

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