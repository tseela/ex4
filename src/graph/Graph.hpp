#pragma once

#include "MatrixClass.hpp"
#include <memory>

/**
 * @brief a direction of a step
 * 
 */
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
    static constexpr auto MIN_STEP_COST = 1;

    /**
     * @brief Construct a new Graph object.
     * 
     * @param matrix - the graph
     * @param startX 
     * @param startY 
     * @param endX 
     * @param endY 
     */
	Graph(const matrix::MatrixClass *matrix, const std::uint32_t startX, const std::uint32_t startY, 
        const std::uint32_t endX, const std::uint32_t endY);

	/**
	 * @brief Returns height of the graph.
	 *
	 * @return uint32_t
	 */
	std::uint32_t getHeight() const;

	/**
	 * @brief Returns width of the graph.
	 *
	 * @return uint32_t
	 */
	std::uint32_t getWidth() const;

    /**
     * @brief Finds the value of the givven cell.
     * 
     * @param x - row
     * @param y - col
     * @return double 
     */
    double operator()(const std::uint32_t x, const std::uint32_t y) const;

    /**
     * @brief Checks if one can step from a cell in a given direction.
     * 
     * @param x - row
     * @param y - col
     * @param direction 
     * @return true 
     * @return false 
     */
    bool canStep(const std::uint32_t x, const std::uint32_t y, const Direction& direction = NONE) const;

    /**
     * @brief Returns the row of the start point.
     * 
     * @return std::uint32_t 
     */
    std::uint32_t startX() const;
    /**
     * @brief Returns the col of the start point.
     * 
     * @return std::uint32_t 
     */
    std::uint32_t startY() const;
    /**
     * @brief Returns the row of the end point.
     * 
     * @return std::uint32_t 
     */
    std::uint32_t endX() const;
    /**
     * @brief Returns the col of the end point.
     * 
     * @return std::uint32_t 
     */
    std::uint32_t endY() const;

    /**
     * @brief Converts the graph into string.
     * 
     * @return std::string 
     */
    std::string to_string() const;

	/**
	 * @brief Destructor for destroying the graph.
	 */
	~Graph();

    /**
     * @brief Converts a direction into string.
     * 
     * @param direction 
     * @return std::string 
     */
    static std::string to_string(const Direction& direction);

    /**
     * @brief Moves (x,y) in the given direction.
     * 
     * @param x - row
     * @param y - col
     * @param direction 
     */
    static void updateByDirection(std::uint32_t& x, std::uint32_t& y, const Direction& direction);

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