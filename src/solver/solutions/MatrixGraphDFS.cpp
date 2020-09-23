#include "MatrixGraphDFS.hpp"

using namespace std;
using namespace graph;
using namespace solver::problem;

solver::string_solution::MatrixGraphDFS::MatrixGraphDFS() {}

string solver::string_solution::MatrixGraphDFS::getOutputFileType() const { return "txt"; }

string solver::string_solution::MatrixGraphDFS::getCacheCode() const { return "matrix_graph"; }

string solver::string_solution::MatrixGraphDFS::getCacheString() const { return "DFS"; }

void solver::string_solution::MatrixGraphDFS::writeToFile(const Problem* graphProblem, const string& fileName) const {
    auto problem = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem));
    auto graph = problem->getGraph();
    string solution = DFS_search(graph);

    if (fileName == PRINT) {
        cout << solution << endl;
    } else {
        files::writeFileContent(fileName, solution);
    }
}

string solver::string_solution::MatrixGraphDFS::getSolutionString(const Problem* graphProblem) const {
    const Graph graph = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem))->getGraph();
    string start = "DFS,";
    return DFS_search(graph, start);
}

string DFS_search(const Graph& graph, string& path) {
    if ()
    return path;
}

int DFS_search(const Graph& graph, int cost) {
    if (graph.)
}