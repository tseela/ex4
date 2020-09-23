#include "MatrixClass.hpp"
#include "MatrixGraphDFS.hpp"
#include "MatrixGraphProblem.hpp"
#include "Solver.hpp"

using namespace std;
using namespace matrix;
using namespace graph;
using namespace solver;

int main() {
    auto matrix = new MatrixClass(2, 2);
    matrix->setValue(0,1, 7);
    matrix->setValue(1, 0, 3);

    auto p = new problem::MatrixGraphProblem(matrix, 0, 0, 1, 1);
    auto s = new MatrixGraphDFS();

    auto solver = new Solver(p, s);
    cout << solver->getStringSolution() << endl;
}