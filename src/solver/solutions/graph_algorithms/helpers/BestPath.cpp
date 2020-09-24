#include "BestPath.hpp"

void BestPath::initialFields(const graph::Graph& graph) {
    // cost will be the sum of all of the vertices in the graph + 1
    // path will be ""
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