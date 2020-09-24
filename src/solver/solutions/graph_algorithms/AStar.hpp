#pragma once

#include "MatrixGraphSolution.hpp"
#include "BestPath.hpp"
#include <queue>
#include <cmath>

namespace AStar {

struct Step {
    std::uint32_t vertex_x;
    std::uint32_t vertex_y;
    std::string my_path;
    double g_cost;
    // will be the minimum cost of the trail from (x, y) to the end point
    double h_func;

    Step(const graph::Graph& graph);
    Step(const graph::Graph& graph, const Step& before, const Direction direction);

    double f();
};

}

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