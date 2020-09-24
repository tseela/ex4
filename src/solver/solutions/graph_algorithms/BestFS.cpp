#include "BestFS.hpp"

using namespace std;
using namespace solver::solution;
using namespace graph;

void BestFS_search(const Graph& graph, BestPath& best);

solver::solution::graph_solution::BestFS::BestFS() {}

string solver::solution::graph_solution::BestFS::getCacheString() const { return "BestFS"; }

string solver::solution::graph_solution::BestFS::algorithm(const Graph& graph) const {
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

    BestFS_search(graph, best);

    if (best.bestPath.compare("") == 0) {
        return "Could not find any path.";
    }

    return to_string(best.bestCost) + "," + getCacheString() + best.bestPath;
}

void BestFS_search(const Graph& graph, BestPath& best) {
        // ppppp
}