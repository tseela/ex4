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

void initializeMatrix(matrix::MatrixClass* matrix) {
    for (auto i = 0; i < matrix->getHeight(); ++i) {
        for (auto j = 0; j < matrix->getWidth(); ++j) {
            matrix->setValue(i, j, (rand() % 999) + 1);
        }
    }
}


int main() {
    string s = "";
    for (auto i = 0; i < 500; ++i) {
        auto x = (rand() % 96) + 5;
        auto y = (rand() % 96) + 5;

        auto matrix = new matrix::MatrixClass(x, y);
        initializeMatrix(matrix);

        s += to_string(x) + "," + to_string(y) + "\n" + matrix->toString() + "\n\n";

        auto p = new problem::MatrixGraphProblem(matrix, 0, 0, matrix->getHeight() - 1, matrix->getWidth() - 1);
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
}