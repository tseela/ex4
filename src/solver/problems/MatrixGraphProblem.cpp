#include "MatrixGraphProblem.hpp"

using namespace std;
using namespace graph;
using namespace matrix;

solver::problem::MatrixGraphProblem::MatrixGraphProblem(const MatrixClass *matrix, uint32_t startX, uint32_t startY, 
    uint32_t endX, uint32_t endY) {
    m_graph = make_unique<Graph>(matrix, startX, startY);
    m_endX = endX;
    m_endY = endY;

    m_cacheString = to_string(crc32FromString(m_graph->toString()));
}

string solver::problem::MatrixGraphProblem::getCacheCode() const { return "graph"; }

string solver::problem::MatrixGraphProblem::getCacheString() const { return m_cacheString; }

double solver::problem::MatrixGraphProblem::getEndX() const { return m_endX; }

double solver::problem::MatrixGraphProblem::getEndY() const { return m_endY; }

Graph solver::problem::MatrixGraphProblem::getGraph() const { return *m_graph; }