#pragma once

#include "MatrixGraphSolution.hpp"
#include "BestPath.hpp"
#include <queue>

struct Step {
    std::uint32_t vertex_x;
    std::uint32_t vertex_y;
    std::string my_path;
    double g_cost;
    // will be the minimum cost of the trail from (x, y) to the end point
    double h_func;
    matrix::MatrixClass isStepped;

    Step(const graph::Graph& graph, const matrix::MatrixClass& steps);
    Step(const graph::Graph& graph, const Step& before, const Direction direction);

    double getf();
};

namespace solver {

namespace solution {

namespace graph_solution {

class AStar : public solver::solution::MatrixGraphSolution {
public:
    AStar();

    std::string getCacheString() const override;

private:
    std::string algorithm(const graph::Graph& graph) const override;
};

}

}

}