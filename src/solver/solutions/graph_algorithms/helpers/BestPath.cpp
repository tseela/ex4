#include "BestPath.hpp"

void BestPath::initialFields(const graph::Graph& graph) {
    bestCost = 1;
    bestPath = "";
    for (uint32_t i = 0; i < graph.getHeight(); ++i) {
        for (uint32_t j = 0; j < graph.getWidth(); ++j) {
            if (graph.canStep(i, j)) {
                bestCost += graph(i, j);
            }
        }
    }
}