#include "MatrixClass.hpp"
#include "BFS.hpp"
#include "DFS.hpp"
#include "AStar.hpp"
#include "MatrixGraphProblem.hpp"
#include "Solver.hpp"
#include "BestFS.hpp"

using namespace std;
using namespace matrix;
using namespace graph;
using namespace solver;
using namespace solver::solution;

int main() {
    auto matrix = new MatrixClass(3, 2);
    matrix->setValue(0, 1, 7);
    matrix->setValue(1, 0, 0);
    matrix->setValue(1, 1, 3);
    matrix->setValue(0, 0, 1);

    matrix->setValue(2, 1, 5);
    matrix->setValue(2, 0, 1);

    auto p = new problem::MatrixGraphProblem(matrix, 0, 0, 1, 1);
    auto dfs = new graph_solution::DFS();
    auto bfs = new graph_solution::BFS();
    auto a_star = new graph_solution::AStar();
    auto best = new graph_solution::BestFS();

    auto solver1 = new Solver(p, dfs);
    auto solver2 = new Solver(p, bfs);
    auto solver3 = new Solver(p, a_star);
    auto solver4 = new Solver(p, best);
    try {
        cout << solver1->getStringSolution(false) << endl;
        cout << solver2->getStringSolution(false) << endl;
        cout << solver3->getStringSolution(false) << endl;
        cout << solver4->getStringSolution(false) << endl;
    } catch (matrix::ErrorCodeException e) {
        e.printErrorMessage();
    }
}