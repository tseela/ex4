#include "BestFS.hpp"

using namespace std;
using namespace solver::solution;
using namespace graph;
using namespace BestFS;

void BestFS_search(const Graph& graph, const matrix::MatrixClass& isStepped, BestPath& best);

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

    BestFS_search(graph, *isStepped, best);

    if (best.bestCost == BestPath::NOT_FOUND) {
        return PATH_NOT_FOUND;
    }

    return to_string(best.bestCost) + "," + getCacheString() + best.bestPath;
}

void BestFS_search(const Graph& graph, const matrix::MatrixClass& isStepped, BestPath& best) {
    // a queue for the vertices we check right now
    queue<Step> open;
    open.push(Step(graph));

    // a vector for the steps we need to check next
    vector<Step> success;
    // a matrix indicator for the vertices we allready checked
    matrix::MatrixClass closed = isStepped;

    while (!open.empty()) {
        Step this_step = open.front();
        open.pop();

        // updates the best cost & path if we make it to the end point
        if (this_step.vertex_x == graph.endX() && this_step.vertex_y == graph.endY()) {
            best.bestCost = this_step.cost;
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

                if (closed(x, y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                    success.push_back(Step(graph, this_step, direction));
                }
            }
        }

        queue<Step> helper;

        // for every step we can make, we will check if it is allready in open.
        // if not, we will add it to open, and else we will keep in open it's "better version"
        // which will be the one with the lower cost.
        for (Step my_step : success) {
            bool isAllreadyHere = false;
            while (!open.empty()) {
                Step step = open.front();
                open.pop();

                // if the step is allready in open, we will put the best version on it in helper
                if (step.vertex_x == my_step.vertex_x && step.vertex_y == my_step.vertex_y) {
                    isAllreadyHere = true;
                    if (my_step.cost < step.cost) {
                        helper.push(my_step);
                        continue;
                    }
                }
                helper.push(step);
            }

            // if my_step isn't in open we will add it here
            if (!isAllreadyHere) {
                helper.push(my_step);
            }

            // when finished, we put all of the 'minimum f' steps in open and keep searching with them
            while (!helper.empty()) {
                open.push(helper.front());
                helper.pop();
            }
        }
        success.clear();
        closed.setValue(this_step.vertex_x, this_step.vertex_y, MatrixGraphSolution::WAS_STEPPED);
    }
    best.bestCost = BestPath::NOT_FOUND;
}

BestFS::Step::Step(const graph::Graph& graph) {
    vertex_x = graph.startX();
    vertex_y = graph.startY();
    my_path = "";
    cost = graph(vertex_x, vertex_y);
}

BestFS::Step::Step(const graph::Graph& graph, const Step& before, const Direction direction) {
    graph::Graph::updateByDirection(vertex_x, vertex_y, direction);
    my_path = before.my_path + "," + graph::Graph::to_string(direction);
    cost = before.cost + graph(vertex_x, vertex_y);
}