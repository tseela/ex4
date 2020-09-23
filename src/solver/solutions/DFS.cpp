#include "DFS.hpp"

using namespace std;

void DFS_search(const graph::Graph& graph, matrix::MatrixClass isStepped, string path, 
double cost, uint32_t x, uint32_t y, BestPath& best);

solver::solution::DFS::DFS() {}

string solver::solution::DFS::getCacheString() const { return "DFS"; }

string solver::solution::DFS::algorithm(const graph::Graph& graph) const {
    auto isStepped = make_unique<matrix::MatrixClass>(graph.getHeight(), graph.getWidth());
    solver::solution::MatrixGraphSolution::initialSteps(*isStepped);
    isStepped->setValue(graph.startX(), graph.startY(), solver::solution::MatrixGraphSolution::WAS_STEPPED);
    BestPath best = BestPath();
    best.initialFields(graph);
    DFS_search(graph, *isStepped, "", 0, graph.startX(), graph.startY(), best);
    return to_string(best.bestCost) + ",DFS" + best.bestPath;
}

void DFS_search(const graph::Graph& graph, matrix::MatrixClass isStepped, string path, 
    double cost, uint32_t x, uint32_t y, BestPath& best) {
    cost += graph(x, y);
    isStepped.setValue(x, y, solver::solution::MatrixGraphSolution::WAS_STEPPED);
    if (graph.endX() == x && graph.endY() == y) {
        if (best.bestCost > cost) {
            best.bestCost = cost;
            best.bestPath = path;
        }
        return;
    }
    if (graph.canStep(x, y, UP)) {
        DFS_search(graph, isStepped, path + ",Up", cost, x, y - 1, best);
    }
    if (graph.canStep(x, y, DOWN)) {
        DFS_search(graph, isStepped, path + ",Down", cost, x, y + 1, best);
    }
    if (graph.canStep(x, y, LEFT)) {
        DFS_search(graph, isStepped, path + ",Left", cost, x - 1, y, best);
    } 
    if (graph.canStep(x, y, RIGHT)) {
        DFS_search(graph, isStepped, path + ",Right", cost, x + 1, y, best);
    }
}

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