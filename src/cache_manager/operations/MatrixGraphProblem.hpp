#pragma once

#include "crc32FileReader.hpp"
#include "Problem.hpp"
#include "Graph.hpp"

#include <string>
#include <memory>

/**
 * @brief This class stands for the "matrix mult" Problem.
 */
class MatrixGraphProblem : public Problem {
public:
    MatrixGraphProblem(const MatrixClass& matrix, std::uint32_t startX, std::uint32_t startY, std::uint32_t endX,
        std::uint32_t endY);
    
    string getCacheCode() const override;

    string getCacheString() const override;

    Graph getGraph() const;

    double getEndX() const;

    double getEndY() const;

private:
    unique_ptr<Graph> m_graph;
    std::uint32_t m_endX;
    std::uint32_t m_endY;
};