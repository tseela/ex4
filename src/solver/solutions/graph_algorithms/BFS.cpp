#include "BFS.hpp"

using namespace std;
using namespace solver::solution;

void BFS_search(const graph::Graph& graph, matrix::MatrixClass isStepped, BestPath& best);

solver::solution::graph_solution::BFS::BFS() {}

string solver::solution::graph_solution::BFS::getCacheString() const { return "BFS"; }

string solver::solution::graph_solution::BFS::algorithm(const graph::Graph& graph) const {
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

    BFS_search(graph, *isStepped, best);

    if (best.bestPath.compare("") == 0) {
        return "Could not find any path.";
    }

    return to_string(best.bestCost) + "," + getCacheString() + best.bestPath;
}

void BFS_search(const graph::Graph& graph, matrix::MatrixClass isStepped, BestPath& best) {
    
}