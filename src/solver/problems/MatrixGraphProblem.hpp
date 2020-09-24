#pragma once

#include "Problem.hpp"
#include "crc32FileReader.hpp"
#include "Graph.hpp"

#include <string>
#include <memory>

namespace solver {

namespace problem {

/**
 * @brief This class stands for the matrix graph Problem.
 */
class MatrixGraphProblem : public Problem {
public:
    /**
     * @brief Construct a new Matrix Graph Problem object.
     * 
     * @param matrix - the graph
     * @param startX 
     * @param startY 
     * @param endX 
     * @param endY 
     */
    MatrixGraphProblem(const matrix::MatrixClass *matrix, const std::uint32_t startX, const std::uint32_t startY, 
        const std::uint32_t endX, const std::uint32_t endY);
    /**
     * @brief Gets the Cache Code of the problem.
     * 
     * @return string 
     */
    string getCacheCode() const override;

    /**
     * @brief Gets the Cache String of the problem (hash of the problem)
     * 
     * @return string 
     */
    string getCacheString() const override;

    /**
     * @brief Gets the pointer of the Graph object of the problem
     * 
     * @return const graph::Graph* 
     */
    const graph::Graph* getGraph() const;

private:
    std::unique_ptr<graph::Graph> m_graph;
};

}

}