#include "Graph.hpp"

using namespace std;

// Checks if (x,y) is a point in the matrix
bool inRange(const matrix::MatrixClass& matrix, const uint32_t x, const uint32_t y) {
    return (x < matrix.getHeight() && y < matrix.getWidth());
}

graph::Graph::Graph(const matrix::MatrixClass *matrix, const uint32_t startX, const uint32_t startY, 
    const uint32_t endX, const uint32_t endY) {
    // throw an error if needed
    if (matrix == nullptr || !inRange(*matrix, startX, startY) || !inRange(*matrix, endX, endY)) {
        throw runtime_error("Error! Invalid arguments for start point or end point.");
    }

    m_matrixGraph = matrix;
    m_start_x = startX;
    m_start_y = startY;
    m_end_x = endX;
    m_end_y = endY;
}

uint32_t graph::Graph::getHeight() const { return m_matrixGraph->getHeight(); }

uint32_t graph::Graph::getWidth() const { return m_matrixGraph->getWidth(); }

double graph::Graph::operator()(const uint32_t x, const uint32_t y) const { return (*m_matrixGraph)(x, y); }

bool graph::Graph::canStep(const std::uint32_t p_x, const std::uint32_t p_y, const Direction& direction /*= NONE*/) const {
    uint32_t x = p_x;
    uint32_t y = p_y;

    // if we can't update p_x & p_y or they will be out of range we return false
    try {
        updateByDirection(x, y, direction);
    } catch (const runtime_error& e) {
        return false;
    }

    if (!inRange(*m_matrixGraph, x, y) || (*m_matrixGraph)(x, y) == BORDER) {
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

graph::Graph::~Graph() { delete(m_matrixGraph); }

string graph::Graph::to_string(const Direction& direction) {
    if (direction == UP) {
        return "Up";
    } else if (direction == DOWN) {
        return "Down";
    } else if (direction == LEFT) {
        return "Left";
    } else if (direction == RIGHT) {
        return "Right";
    }
    return "";
}

void graph::Graph::updateByDirection(uint32_t& x, uint32_t& y, const Direction& direction) {
    if ((direction == LEFT && y == 0) || (x == 0 && direction == UP)) {
        throw runtime_error("Error! Can't update the point as needed. x & y must be bigger then 0.");
    }

    if (direction == UP) {
        --x;
    } else if (direction == DOWN) {
        ++x;
    } else if (direction == LEFT) {
        --y;
    } else if (direction == RIGHT) {
        ++y;
    }
}
