#include "MatrixGraphDFS.hpp"

using namespace std;
using namespace graph;
using namespace solver::problem;

solver::MatrixGraphDFS::MatrixGraphDFS() {}

string solver::MatrixGraphDFS::getOutputFileType() const { return "txt"; }

string solver::MatrixGraphDFS::getCacheCode() const { return "matrix_graph"; }

string solver::MatrixGraphDFS::getCacheString() const { return "DFS"; }

void solver::MatrixGraphDFS::writeToFile(const Problem* graphProblem, const string& fileName) const {
    auto problem = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem));
    auto graph = problem->getGraph();
    string solution = DFS_search(graph);

    if (fileName == PRINT) {
        cout << solution << endl;
    } else {
        files::writeFileContent(fileName, solution);
    }
}

string solver::MatrixGraphDFS::getSolutionString(const Problem* graphProblem) const {
    const Graph graph = dynamic_cast<MatrixGraphProblem *>(const_cast<Problem *>(graphProblem))->getGraph();
    string start = "DFS,";
    return DFS_search(graph, start);
}

string DFS_search(const Graph& graph, string& path) {
    if ()
    return path;
}

double DFS_search(const Graph& graph, uint32_t endX, uint32_t endY, double cost) {
    auto x = graph.getX();
    auto y = graph.getY();
    if (x == endX && x == endY) {
        return cost + graph(x, y);
    }

}