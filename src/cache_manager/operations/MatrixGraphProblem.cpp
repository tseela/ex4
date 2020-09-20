#include "MatrixGraphProblem.hpp"

using namespace OperatorsHelpingFuncs;
using namespace std;

MatrixGraphProblem::MatrixGraphProblem(const MatrixClass& matrix) {
    graph = make_unique<MatrixClass>(matrix);

    m_cacheString = getCacheCode() + " ";
    m_cacheString += to_string(crc32FromString(graph->toString()));
}

string MatrixGraphProblem::getCacheCode() const { return "graph"; }

string MatrixGraphProblem::getCacheString() const { return m_cacheString; }

MatrixClass MatrixGraphProblem::getGraph() const { return *graph; }