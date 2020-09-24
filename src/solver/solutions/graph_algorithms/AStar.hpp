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

    /**
     * @brief Construct a new Step object
     *        Which is the first step in the graph.
     * 
     * @param graph 
     */
    Step(const graph::Graph& graph);
    /**
     * @brief Construct a new Step object.
     * 
     * @param graph 
     * @param before - the last step we took
     * @param direction - the direction we needed to step to make it to this cell
     */
    Step(const graph::Graph& graph, const Step& before, const Direction direction);

    double f();
};

}

namespace solver {

namespace solution {

namespace graph_solution {

class AStar : public solver::solution::MatrixGraphSolution {
public:
    /**
     * @brief Construct a new AStar object.
     * 
     */
    AStar();

    std::string getCacheString() const override;

private:
    std::string algorithm(const graph::Graph& graph) const override;
};

}

}

}