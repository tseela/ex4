#include "MatrixGraphSolution.hpp"

using namespace std;
using namespace graph;
using namespace solver::problem;

solver::solution::MatrixGraphSolution::MatrixGraphSolution() {}

string solver::solution::MatrixGraphSolution::getOutputFileType() const { return "txt"; }

string solver::solution::MatrixGraphSolution::getCacheCode() const { return "graph"; }

void solver::solution::MatrixGraphSolution::writeToFile(const Problem* graphProblem, const string& fileName) const {
    auto problem = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem));
    auto graph = problem->getGraph();
    string solution = solver::solution::MatrixGraphSolution::algorithm(*graph);

    if (fileName == PRINT) {
        cout << solution << endl;
    } else {
        files::writeFileContent(fileName, solution);
    }
}

string solver::solution::MatrixGraphSolution::getSolutionString(const Problem* graphProblem) const {
    auto problem = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem));
    auto graph = problem->getGraph();
    return solver::solution::MatrixGraphSolution::algorithm(*graph);
}

void solver::solution::MatrixGraphSolution::initialSteps(matrix::MatrixClass& steps) {
    for (uint32_t i = 0; i < steps.getHeight(); ++i) {
        for (uint32_t j = 0; j < steps.getWidth(); ++j) {
            steps.setValue(i, j, solver::solution::MatrixGraphSolution::WAS_NOT_STEPPED);
        }
    }
}