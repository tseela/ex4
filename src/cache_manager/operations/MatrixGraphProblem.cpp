#include "MatrixGraphProblem.hpp"

using namespace std;

MatrixGraphProblem::MatrixGraphProblem(const MatrixClass& matrix, uint32_t startX, uint32_t startY, uint32_t endX,
    uint32_t endY) {
    m_graph = make_unique<Graph>(matrix, startX, startY);
    m_endX = endX;
    m_endY = endY;

    m_cacheString = getCacheCode() + " ";
    m_cacheString += to_string(crc32FromString(m_graph->toString()));
}

string MatrixGraphProblem::getCacheCode() const { return "graph"; }

string MatrixGraphProblem::getCacheString() const { return m_cacheString; }

double MatrixGraphProblem::getEndX() const { return m_endX; }

double MatrixGraphProblem::getEndY() const { return m_endY; }

Graph MatrixGraphProblem::getGraph() const { return *m_graph; }