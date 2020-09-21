#include "Graph.hpp"

using namespace std;

Graph::Graph(const MatrixClass& matrix, uint32_t startX, uint32_t startY) {
    m_matrixGraph = matrix;
    m_steps = MatrixClass(matrix.getHeight(), matrix.getWidth());
    m_steps.setValue(startX, startY, true);
    m_x = startX;
    m_y = startY;
    m_cost = matrix(startX, startY);
}

uint32_t Graph::getHeight() const { return m_matrixGraph.getHeight(); }

uint32_t Graph::getWidth() const { return m_matrixGraph.getWidth(); }

double Graph::operator()(uint32_t x, uint32_t y) const { return m_matrixGraph(x, y); }

bool Graph::step(Direction& direction) {
    switch(direction) {
        case NONE:
            return false;
        case UPP:
            if (m_y - 1 < 0) {
                return false;
            }
            --m_y;
            break;
        case DOWN:
            if (m_y + 1 > m_matrixGraph.getHeight()) {
                return false;
            }
            ++m_y;
            break;
        case LEFT:
            if (m_x - 1 < 0) {
                return false;
            }
            --m_x;
            break;
        case RIGHT:
            if (m_x + 1 > m_matrixGraph.getHeight()) {
                return false;
            }
            ++m_x;
            break;
    }

    m_steps.setValue(m_x, m_y, true);
    m_cost += m_matrixGraph(m_x, m_y);
    return true;
}

bool Graph::wasStepped(uint32_t x, uint32_t y) const {
    return m_steps(x, y) != 0;
}

bool Graph::wasStepped(uint32_t x, uint32_t y, Direction& direction) const {
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

string Graph::toString() const { return m_matrixGraph.toString(); }

double Graph::getCost() const { return m_cost; }

Graph::~Graph() {
    delete(&m_matrixGraph);
    delete(&m_steps);
}