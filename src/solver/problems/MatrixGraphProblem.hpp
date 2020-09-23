#pragma once

#include "Problem.hpp"
#include "crc32FileReader.hpp"
#include "Graph.hpp"

#include <string>
#include <memory>

namespace solver {

namespace problem {

/**
 * @brief This class stands for the "matrix mult" Problem.
 */
class MatrixGraphProblem : public Problem {
public:
    MatrixGraphProblem(const matrix::MatrixClass *matrix, std::uint32_t startX, std::uint32_t startY, 
        std::uint32_t endX, std::uint32_t endY);
    
    string getCacheCode() const override;

    string getCacheString() const override;

    graph::Graph& getGraph() const;

    double getEndX() const;

    double getEndY() const;

private:
    unique_ptr<graph::Graph> m_graph;
    std::uint32_t m_endX;
    std::uint32_t m_endY;
};

}

}