#include "Graph.hpp"

using namespace std;

graph::Graph::Graph(const matrix::MatrixClass *matrix, uint32_t startX, uint32_t startY, 
    uint32_t endX, uint32_t endY) {
    m_matrixGraph = matrix;
    m_start_x = startX;
    m_start_y = startY;
    m_end_x = endX;
    m_end_y = endY;
}

uint32_t graph::Graph::getHeight() const { return m_matrixGraph->getHeight(); }

uint32_t graph::Graph::getWidth() const { return m_matrixGraph->getWidth(); }

double graph::Graph::operator()(uint32_t x, uint32_t y) const { return (*m_matrixGraph)(x, y); }

bool graph::Graph::canStep(std::uint32_t p_x, std::uint32_t p_y, const Direction& direction /*= NONE*/) const {
    int x = p_x;
    int y = p_y;
    if (direction == UP) {
        --x;
    } else if (direction == DOWN) {
        ++x;
    } else if (direction == LEFT) {
        --y;
    } else if (direction == RIGHT) {
        ++y;
    }

    if (x < 0 || y < 0 || x >= static_cast<int>(m_matrixGraph->getHeight()) || 
        y >= static_cast<int>(m_matrixGraph->getWidth()) || (*m_matrixGraph)(x, y) == BORDER) {
        return false;
    }
    return true;
}

uint32_t graph::Graph::startX() const { return m_start_x; }
uint32_t graph::Graph::startY() const { return m_start_y; }
uint32_t graph::Graph::endX() const { return m_end_x; }
uint32_t graph::Graph::endY() const { return m_end_y; }

string graph::Graph::to_string() const {
    string s = std::to_string(static_cast<int>(m_start_x)) + "|" + std::to_string(static_cast<int>(m_start_y));
    s += "|" + m_matrixGraph->toString() + "|";
    s += std::to_string(static_cast<int>(m_end_x)) + "|" + std::to_string(static_cast<int>(m_end_y));
    return s;
}

graph::Graph::~Graph() {
    delete(m_matrixGraph);
}