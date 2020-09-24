#include "BFS.hpp"

using namespace std;
using namespace solver::solution;
using namespace BFS;

void BFS_search(const graph::Graph& graph, const matrix::MatrixClass& isStepped, BestPath& best);

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

    BFS_search(graph, *isStepped, best);

    if (best.bestPath.empty()) {
        return PATH_NOT_FOUND;
    }

    return to_string(best.bestCost) + "," + getCacheString() + best.bestPath;
}

void BFS_search(const graph::Graph& graph, const matrix::MatrixClass& isStepped, BestPath& best) {
    queue<Step> trails;
    trails.push(Step(graph.startX(), graph.startY(), "", graph(graph.startX(), graph.startY())));

    auto steps = isStepped;

    while (!trails.empty()) {
        Step this_step = trails.front();
        trails.pop();

        // if this is the end point we will save it and return
        if (this_step.vertex_x == graph.endX() && this_step.vertex_y == graph.endY()) {
            best.bestCost = this_step.my_cost;
            best.bestPath = this_step.my_path;
            return;
        }

        vector<Direction> all_directions;
        all_directions.push_back(UP);
        all_directions.push_back(DOWN);
        all_directions.push_back(LEFT);
        all_directions.push_back(RIGHT);

        // we will try to move in any direction
        for (Direction direction : all_directions) {
            auto x = this_step.vertex_x;
            auto y = this_step.vertex_y;

            // only if we can move in the direction we will update x & y.
            // if we won't check the step an exception might be thrown.
            if (graph.canStep(this_step.vertex_x, this_step.vertex_y, direction)) {
                graph::Graph::updateByDirection(x, y, direction);

                if (steps(x, y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                    steps.setValue(x, y, MatrixGraphSolution::WAS_STEPPED);
                    trails.push(Step(graph, this_step, direction));
                }
            }
        }
    }
    best.bestCost = BestPath::NOT_FOUND;
}

Step::Step(const std::uint32_t x, const std::uint32_t y, const std::string& path, const double cost) {
    vertex_x = x;
    vertex_y = y;
    my_path = path;
    my_cost = cost;
}

Step::Step(const graph::Graph& graph, const Step& before, const Direction direction) {
    auto x = before.vertex_x;
    auto y = before.vertex_y;

    my_path = before.my_path + "," + graph::Graph::to_string(direction);

    graph::Graph::updateByDirection(x, y, direction);
    
    my_cost = before.my_cost + graph(x, y);
    vertex_x = x;
    vertex_y = y;
}