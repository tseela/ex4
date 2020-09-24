#pragma once

#include "Graph.hpp"
#include <string>

/**
 * @brief A struct with cost & path (for the solution of the matrix graph problem).
 * 
 */
struct BestPath {
    double bestCost;
    std::string bestPath;

    /**
     * @brief Initials the fields for the algorithm.
     * 
     * @param graph 
     */
    void initialFields(const graph::Graph& graph);
};