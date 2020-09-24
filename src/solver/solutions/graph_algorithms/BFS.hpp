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

    Step(const std::uint32_t x, const std::uint32_t y, const std::string& path, const double cost,
        const matrix::MatrixClass& steps);
    Step(const graph::Graph& graph, const Step& before, const Direction direction);
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