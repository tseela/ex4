#include "DFS.hpp"

using namespace std;
using namespace solver::solution;
using namespace graph;

void DFS_search(const Graph& graph, matrix::MatrixClass isStepped, string path, 
double cost, uint32_t x, uint32_t y, BestPath& best);

solver::solution::graph_solution::DFS::DFS() {}

string solver::solution::graph_solution::DFS::getCacheString() const { return "DFS"; }

string solver::solution::graph_solution::DFS::algorithm(const Graph& graph) const {
    // if the end point and the start point are the same, the cost is 0
    if (graph.startX() == graph.endX() && graph.startY() == graph.endY()) {
        return "0," + getCacheString();
    }

    // creating & initializing a matrix for tracking our steps (the start point is allready stepped)
    auto isStepped = make_unique<matrix::MatrixClass>(graph.getHeight(), graph.getWidth());
    solver::solution::MatrixGraphSolution::initialSteps(*isStepped);
    isStepped->setValue(graph.startX(), graph.startY(), MatrixGraphSolution::WAS_STEPPED);

    BestPath best = BestPath();
    best.initialFields(graph);

    DFS_search(graph, *isStepped, "", 0, graph.startX(), graph.startY(), best);

    if (best.bestPath.compare("") == 0) {
        return "Could not find any path.";
    }

    return to_string(best.bestCost) + "," + getCacheString() + best.bestPath;
}

void DFS_search(const Graph& graph, matrix::MatrixClass isStepped, string path, 
    double cost, uint32_t x, uint32_t y, BestPath& best) {
    
    cost += graph(x, y);
    isStepped.setValue(x, y, MatrixGraphSolution::WAS_STEPPED);

    // if out start point equals to the end point we will return and update the best cost & path
    if (graph.endX() == x && graph.endY() == y) {
        if (best.bestCost > cost) {
            best.bestCost = cost;
            best.bestPath = path;
        }
        return;
    }

    // if we can make a step (in any direction) we will make it and activate our recursive func on it
    if (graph.canStep(x, y, UP) && isStepped(x - 1, y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
        DFS_search(graph, isStepped, path + "," + to_string(UP), cost, x - 1, y, best);
    }

    if (graph.canStep(x, y, DOWN) && isStepped(x + 1, y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
        DFS_search(graph, isStepped, path + "," + to_string(DOWN), cost, x + 1, y, best);
    }

    if (graph.canStep(x, y, LEFT) && isStepped(x, y - 1) == MatrixGraphSolution::WAS_NOT_STEPPED) {
        DFS_search(graph, isStepped, path + "," + to_string(LEFT), cost, x, y - 1, best);
    }

    if (graph.canStep(x, y, RIGHT) && isStepped(x, y + 1) == MatrixGraphSolution::WAS_NOT_STEPPED) {
        DFS_search(graph, isStepped, path + "," + to_string(RIGHT), cost, x, y + 1, best);
    }
}