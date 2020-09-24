#pragma once

#include "MatrixGraphSolution.hpp"
#include "BestPath.hpp"
#include <queue>

namespace BFS {

/**
 * @brief Stands for one step in the graph.
 * 
 */
struct Step {
    std::uint32_t vertex_x;
    std::uint32_t vertex_y;
    std::string my_path;
    double my_cost;
    matrix::MatrixClass isStepped;

    /**
     * @brief Construct a new Step object.
     * 
     * @param x - row
     * @param y - col
     * @param path - path untill this cell
     * @param cost - cost of the path
     * @param steps - the famuos steps matrix
     */
    Step(const std::uint32_t x, const std::uint32_t y, const std::string& path, const double cost,
        const matrix::MatrixClass& steps);
    /**
     * @brief Construct a new Step object.
     * 
     * @param graph 
     * @param before - the step that led to this one
     * @param direction - the direction we stepped in to make into the next cell
     */
    Step(const graph::Graph& graph, const Step& before, const Direction direction);
};

}

namespace solver {

namespace solution {

namespace graph_solution {

class BFS : public solver::solution::MatrixGraphSolution {
public:
    /**
     * @brief Construct a new BFS object.
     * 
     */
    BFS();

    std::string getCacheString() const override;

private:
    std::string algorithm(const graph::Graph& graph) const override;
};

}

}

}