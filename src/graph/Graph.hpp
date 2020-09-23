#pragma once

#include "MatrixClass.hpp"
#include <memory>

enum Direction {
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

namespace graph {

class Graph {
public:
    static constexpr auto BORDER = 0;

	Graph(const matrix::MatrixClass *matrix, std::uint32_t startX, std::uint32_t startY, 
        std::uint32_t endX, std::uint32_t endY);

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

    bool canStep(std::uint32_t x, std::uint32_t y, const Direction& direction = NONE) const;

    std::uint32_t startX() const;
    std::uint32_t startY() const;
    std::uint32_t endX() const;
    std::uint32_t endY() const;

    std::string to_string() const;

	/**
	 * @brief Destructor for destroying the graph.
	 */
	~Graph();

private:

    const matrix::MatrixClass *m_matrixGraph;

    // start point
    std::uint32_t m_start_x;
    std::uint32_t m_start_y;

    // end point
    std::uint32_t m_end_x;
    std::uint32_t m_end_y;
};

}