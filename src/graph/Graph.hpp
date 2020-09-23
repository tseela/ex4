#pragma once

#include "MatrixClass.hpp"
#include <memory>

enum Direction {
    NONE = 0,
    UPP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

namespace graph {

class Graph {
public:
    static constexpr int BORDER = 0;

	Graph(const matrix::MatrixClass *matrix, std::uint32_t startX, std::uint32_t startY);

	/**
	 * @brief Returns height of given graph.
	 *
	 * @return uint32_t
	 */
	std::uint32_t getHeight() const;

	/**
	 * @brief Returns width of graph.
	 *
	 * @return uint32_t
	 */
	std::uint32_t getWidth() const;

    double operator()(std::uint32_t x, std::uint32_t y) const;

    bool step(Direction& direction);

    bool wasStepped(std::uint32_t x, std::uint32_t y) const;

    bool wasStepped(std::uint32_t x, std::uint32_t y, Direction& direction) const;

    string toString() const;

    double getCost() const;

	/**
	 * @brief Destructor for destroying the graph.
	 */
	~Graph();

private:
    void stepOnBorders();


    const matrix::MatrixClass *m_matrixGraph;
    // m_steps(i, j) = 0 --> the cell wasn't stepped yet (else, we stepped on this one allready)
    std::unique_ptr<matrix::MatrixClass> m_steps;

    // the cost of the path we made this far
    double m_cost;

    // current point
    std::uint32_t m_x;
    std::uint32_t m_y;
};

}