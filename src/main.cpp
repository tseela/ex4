#include "MatrixClass.hpp"
#include "DFS.hpp"
#include "MatrixGraphProblem.hpp"
#include "Solver.hpp"

using namespace std;
using namespace matrix;
using namespace graph;
using namespace solver;
using namespace solver::solution;

int main() {
    auto matrix = new MatrixClass(3, 2);
    matrix->setValue(0, 1, 7);
    matrix->setValue(1, 0, 0);
    matrix->setValue(2, 1, 5);
    matrix->setValue(2, 0, 1);
    matrix->setValue(1, 1, 3);
    matrix->setValue(0, 0, 1);

    auto p = new problem::MatrixGraphProblem(matrix, 0, 0, 2, 1);
    auto s = new graph_solution::DFS();

    auto solver = new Solver(p, s);
    try {
        cout << solver->getStringSolution() << endl;
        cout << solver->getStringSolution() << endl;
    } catch (matrix::ErrorCodeException e) {
        e.printErrorMessage();
    }
}