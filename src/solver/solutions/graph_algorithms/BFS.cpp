#include "BFS.hpp"

using namespace std;
using namespace solver::solution;

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
    best.initialFields(graph);

    BFS_search(graph, *isStepped, best);

    if (best.bestPath.compare("") == 0) {
        return "Could not find any path.";
    }

    return to_string(best.bestCost) + "," + getCacheString() + best.bestPath;
}

void BFS_search(const graph::Graph& graph, const matrix::MatrixClass& isStepped, BestPath& best) {
    queue<Step> trails;
    trails.push(Step(graph.startX(), graph.startY(), "", graph(graph.startX(), graph.startY()), isStepped));

    while(!trails.empty()) {
        Step this_step = trails.front();
        trails.pop();

        if (this_step.vertex_x == graph.endX() && this_step.vertex_y == graph.endY()) {
            if (best.bestCost > this_step.my_cost) {
                best.bestCost = this_step.my_cost;
                best.bestPath = this_step.my_path;
            }
            continue;
        }

        // if we can make a step (in any direction) we will push it's trail into our queue
        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, UP) && 
            this_step.isStepped(this_step.vertex_x - 1, this_step.vertex_y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                trails.push(Step(graph, this_step, UP));
        }

        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, DOWN) && 
            this_step.isStepped(this_step.vertex_x + 1, this_step.vertex_y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                trails.push(Step(graph, this_step, DOWN));
        }

        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, LEFT) && 
            this_step.isStepped(this_step.vertex_x, this_step.vertex_y - 1) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                trails.push(Step(graph, this_step, LEFT));
        }

        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, RIGHT) && 
            this_step.isStepped(this_step.vertex_x, this_step.vertex_y + 1) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                trails.push(Step(graph, this_step, RIGHT));
        }
    }
}

Step::Step(const std::uint32_t x, const std::uint32_t y, const std::string& path, const double cost,
    const matrix::MatrixClass& steps) : isStepped(steps) {
        vertex_x = x;
        vertex_y = y;
        my_path = path;
        my_cost = cost;
}

Step::Step(const graph::Graph& graph, const Step& before, const Direction direction) : isStepped(before.isStepped) {
    auto x = before.vertex_x;
    auto y = before.vertex_y;

    my_path = before.my_path + "," + graph::Graph::to_string(direction);
    isStepped.setValue(x, y, MatrixGraphSolution::WAS_STEPPED);

    graph::Graph::updateByDirection(x, y, direction);
    
    my_cost = before.my_cost + graph(x, y);
    vertex_x = x;
    vertex_y = y;
}