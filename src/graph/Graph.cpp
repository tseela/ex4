#include "Graph.hpp"

using namespace std;

graph::Graph::Graph(const matrix::MatrixClass *matrix, uint32_t startX, uint32_t startY) {
    m_matrixGraph = matrix;
    m_steps = make_unique<matrix::MatrixClass>(matrix->getHeight(), matrix->getWidth());
    stepOnBorders();
    m_x = startX;
    m_y = startY;
    m_cost = 0;
}

uint32_t graph::Graph::getHeight() const { return m_matrixGraph->getHeight(); }

uint32_t graph::Graph::getWidth() const { return m_matrixGraph->getWidth(); }

double graph::Graph::operator()(uint32_t x, uint32_t y) const { return (*m_matrixGraph)(x, y); }

bool graph::Graph::step(Direction& direction) {
    auto x = m_x;
    auto y = m_y;

    switch(direction) {
        case NONE:
            return false;
        case UPP:
            if (y == 0) {
                return false;
            }
            --y;
            break;
        case DOWN:
            if (y + 1 > m_matrixGraph->getHeight()) {
                return false;
            }
            ++y;
            break;
        case LEFT:
            if (x == 0) {
                return false;
            }
            --x;
            break;
        case RIGHT:
            if (x + 1 > m_matrixGraph->getHeight()) {
                return false;
            }
            ++x;
            break;
    }

    m_steps->setValue(m_x, m_y, true);
    m_cost += (*m_matrixGraph)(m_x, m_y);

    m_y = y;
    m_x = x;
    return true;
}

bool graph::Graph::wasStepped(uint32_t x, uint32_t y) const {
    return (*m_steps)(x, y) != 0;
}

bool graph::Graph::wasStepped(uint32_t x, uint32_t y, Direction& direction) const {
    if (direction == UPP) {
        --y;
    } else if (direction == DOWN) {
        ++y;
    } else if (direction == LEFT) {
        --x;
    } else if (direction == RIGHT) {
        ++x;
    }

    return wasStepped(x, y);
}

string graph::Graph::toString() const { return m_matrixGraph->toString(); }

double graph::Graph::getCost() const { return m_cost; }

uint32_t graph::Graph::getX() const { return m_x; }
uint32_t graph::Graph::getY() const { return m_y; }

graph::Graph::~Graph() {
    delete(m_matrixGraph);
}

void graph::Graph::stepOnBorders() {
    for (uint32_t i = 0; i < m_steps->getHeight(); ++i) {
        for (uint32_t j = 0; j < m_steps->getWidth(); ++j) {
            if ((*m_matrixGraph)(i, j) == BORDER) {
                m_steps->setValue(i, j, true);
            }
        }
    }
}