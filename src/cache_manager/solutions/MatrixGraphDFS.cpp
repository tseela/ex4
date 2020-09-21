#include "MatrixGraphDFS.hpp"

using namespace std;

string MatrixGraphDFS::getOutputFileType() const { return "txt"; }

string MatrixGraphDFS::getCacheCode() const { return "matrix_graph"; }

void MatrixGraphDFS::writeToFile(Problem* const graphProblem, const string& fileName) const {
    // implement "rule of 5" in MatrixClass and the next line will work:
    const Graph graph = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem))->getGraph();
    string solution = DFS_search(graph);

    if (fileName == PRINT) {
        cout << solution << endl;
    } else {
        writeFileContent(fileName, solution);
    }
}

string MatrixGraphDFS::getSolutionString(Problem* const graphProblem) const {
    // implement "rule of 5" in MatrixClass and the next line will work:
    const Graph graph = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem))->getGraph();
    return DFS_search(graph);
}

string DFS_search(const Graph& graph) {
    string solution = "";

    // dfs algorithem

    return solution;
}