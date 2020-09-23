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
            isStepped(this_step.vertex_x - 1, this_step.vertex_y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                trails.push(Step(graph, this_step, UP));
        }

        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, DOWN) && 
            isStepped(this_step.vertex_x + 1, this_step.vertex_y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                trails.push(Step(graph, this_step, DOWN));
        }

        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, LEFT) && 
            isStepped(this_step.vertex_x, this_step.vertex_y - 1) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                trails.push(Step(graph, this_step, LEFT));
        }

        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, RIGHT) && 
            isStepped(this_step.vertex_x, this_step.vertex_y + 1) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                trails.push(Step(graph, this_step, RIGHT));
        }
    }
}

Step::Step(std::uint32_t x, std::uint32_t y, std::string path, double cost, matrix::MatrixClass steps) {
    vertex_x = x;
    vertex_y = y;
    my_path = path;
    my_cost = cost;
    isStepped = steps;
}

Step::Step(const graph::Graph& graph, Step before, Direction direction) {
    auto x = before.vertex_x;
    auto y = before.vertex_y;
    my_path = before.my_path + "," + to_string(direction);
    my_cost = before.my_cost + graph(x, y);
    before.isStepped.setValue(x, y, MatrixGraphSolution::WAS_STEPPED);
    isStepped = before.isStepped;

    if (direction == UP) {
        --y;
    } else if (direction == DOWN) {
        ++y;
    } else if (direction == LEFT) {
        --x;
    } else if (direction == RIGHT) {
        ++x;
    }

    vertex_x = x;
    vertex_y = y;
}