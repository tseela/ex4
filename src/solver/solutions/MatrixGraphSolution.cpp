#include "MatrixGraphSolution.hpp"

using namespace std;
using namespace graph;
using namespace solver::problem;

solver::MatrixGraphSolution::MatrixGraphSolution() {}

string solver::MatrixGraphSolution::getOutputFileType() const { return "txt"; }

string solver::MatrixGraphSolution::getCacheCode() const { return "graph"; }

void solver::MatrixGraphSolution::writeToFile(const Problem* graphProblem, const string& fileName) const {
    // auto problem = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem));
    // auto graph = problem->getGraph();
    string solution = "DFS," + graphProblem->getCacheCode();
    //solution = DFS_search(*graph, solution);

    if (fileName == PRINT) {
        cout << solution << endl;
    } else {
        files::writeFileContent(fileName, solution);
    }
}

string solver::MatrixGraphSolution::getSolutionString(const Problem* graphProblem) const {
    // auto problem = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem));
    // auto graph = problem->getGraph();
    string solution = "DFS," + graphProblem->getCacheCode();
    //solution = DFS_search(*graph, solution);
    return solution;
}