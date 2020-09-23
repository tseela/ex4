#pragma once

#include "Graph.hpp"
#include <string>

struct BestPath {
    double bestCost;
    std::string bestPath;

    void initialFields(const graph::Graph& graph);
};