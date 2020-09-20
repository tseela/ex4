#include "MatrixGraphDFS.hpp"

using namespace std;

string MatrixGraphDFS::getOutputFileType() const { return "txt"; }

string MatrixGraphDFS::getCacheCode() const { return "matrix_graph"; }

void MatrixGraphDFS::writeToFile(Problem* graphProblem, const string& fileName) const {
    string solution = "";
    // dfs algorithem

    if (fileName == PRINT) {
        cout << solution << endl;
    } else {
        writeFileContent(fileName, solution);
    }
}