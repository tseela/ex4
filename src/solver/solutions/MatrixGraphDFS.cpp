#include "MatrixGraphDFS.hpp"

using namespace std;
using namespace graph;
using namespace solver::problem;

solver::MatrixGraphDFS::MatrixGraphDFS() {}

string solver::MatrixGraphDFS::getOutputFileType() const { return "txt"; }

string solver::MatrixGraphDFS::getCacheCode() const { return "graph"; }

string solver::MatrixGraphDFS::getCacheString() const { return "DFS"; }

void solver::MatrixGraphDFS::writeToFile(const Problem* graphProblem, const string& fileName) const {
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

string solver::MatrixGraphDFS::getSolutionString(const Problem* graphProblem) const {
    // auto problem = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem));
    // auto graph = problem->getGraph();
    string solution = "DFS," + graphProblem->getCacheCode();
    //solution = DFS_search(*graph, solution);
    return solution;
}