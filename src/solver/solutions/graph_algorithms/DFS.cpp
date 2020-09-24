#include "DFS.hpp"

using namespace std;
using namespace solver::solution;
using namespace graph;

void DFS_search(const Graph&, matrix::MatrixClass&, const string&, const double, const uint32_t, const uint32_t, BestPath&);

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
        return PATH_NOT_FOUND;
    }

    return to_string(best.bestCost) + "," + getCacheString() + best.bestPath;
}

void DFS_search(const Graph& graph, matrix::MatrixClass& isStepped, const string& p_path, 
    const double p_cost, const uint32_t x, const uint32_t y, BestPath& best) {
    
    string path = p_path;
    double cost = p_cost;
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

    vector<Direction> all_directions;
    all_directions.push_back(UP);
    all_directions.push_back(DOWN);
    all_directions.push_back(LEFT);
    all_directions.push_back(RIGHT);

    // we will try to move in any direction
    for (Direction direction : all_directions) {
        auto try_x = x;
        auto try_y = y;

        // only if we can move in the direction we will update x & y.
        // if we won't check the step an exception might be thrown.
        if (graph.canStep(x, y, direction)) {
            graph::Graph::updateByDirection(try_x, try_y, direction);

            if (isStepped(try_x, try_y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                DFS_search(graph, isStepped, path + "," + graph::Graph::to_string(direction), cost, try_x, try_y, best);
            }
        }
    }
}