#include "AStar.hpp"

using namespace std;
using namespace solver::solution;
using namespace graph;

void AStar_search(const Graph& graph, matrix::MatrixClass isStepped, string path, 
double cost, uint32_t x, uint32_t y, BestPath& best);

solver::solution::graph_solution::AStar::AStar() {}

string solver::solution::graph_solution::AStar::getCacheString() const { return "AStar"; }

string solver::solution::graph_solution::AStar::algorithm(const Graph& graph) const {
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

    AStar_search(graph, *isStepped, "", 0, graph.startX(), graph.startY(), best);

    if (best.bestPath.compare("") == 0) {
        return "Could not find any path.";
    }

    return to_string(best.bestCost) + "," + getCacheString() + best.bestPath;
}

void AStar_search(const Graph& graph, matrix::MatrixClass isStepped, string path, 
    double cost, uint32_t x, uint32_t y, BestPath& best) {
    
    queue<Step> trails;
    trails.push(Step(graph, isStepped));

    vector<Step> success;

    while (!trails.empty()) {
        Step this_step = trails.front();
        trails.pop();

        if (this_step.vertex_x == graph.endX() && this_step.vertex_y == graph.endY()) {
            if (best.bestCost > this_step.g_cost) {
                best.bestCost = this_step.g_cost;
                best.bestPath = this_step.my_path;
            }
            continue;
        }

        // if we can make a step (in any direction) we will push it's trail into our success queue
        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, UP) && 
            this_step.isStepped(this_step.vertex_x - 1, this_step.vertex_y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                success.push_back(Step(graph, this_step, UP));
        }

        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, DOWN) && 
            this_step.isStepped(this_step.vertex_x + 1, this_step.vertex_y) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                success.push_back(Step(graph, this_step, DOWN));
        }

        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, LEFT) && 
            this_step.isStepped(this_step.vertex_x, this_step.vertex_y - 1) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                success.push_back(Step(graph, this_step, LEFT));
        }

        if (graph.canStep(this_step.vertex_x, this_step.vertex_y, RIGHT) && 
            this_step.isStepped(this_step.vertex_x, this_step.vertex_y + 1) == MatrixGraphSolution::WAS_NOT_STEPPED) {
                success.push_back(Step(graph, this_step, RIGHT));
        }

        for (auto i = 0; i < success.size(); ++i) {
            if (graph.canStep(success.at(i).vertex_x, success.at(i).vertex_y)) {
                // do something
            }
        }
        success.clear();
    }
}

Step::Step(const graph::Graph& graph, const matrix::MatrixClass& steps) : isStepped(steps) {
    vertex_x = graph.startX();
    vertex_y = graph.startY();
    my_path = "";
    g_cost = graph(vertex_x, vertex_y);
    h_func = 0;
}

Step::Step(const graph::Graph& graph, const Step& before, const Direction direction) : isStepped(before.isStepped) {
    graph::Graph::updateByDirection(vertex_x, vertex_y, direction);
    isStepped.setValue(vertex_x, vertex_y, MatrixGraphSolution::WAS_STEPPED);
    my_path = before.my_path + "," + graph::Graph::to_string(direction);
    g_cost = before.g_cost + graph(vertex_x, vertex_y);
    h_func = graph::Graph::MIN_STEP_COST * (abs(vertex_x - graph.endX()) + abs(vertex_y - graph.endY()));
}

double Step::getf() { return h_func + g_cost; }