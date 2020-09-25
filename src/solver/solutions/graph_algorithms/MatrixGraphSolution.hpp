#pragma once

#include "MatrixGraphProblem.hpp"
#include "Solution.hpp"
#include <iostream>
#include <string_view>

namespace solver {

namespace solution {

class MatrixGraphSolution : public solver::Solution {
public:
    static constexpr auto WAS_STEPPED = 1;
    static constexpr auto WAS_NOT_STEPPED = 0;
    static constexpr auto PATH_NOT_FOUND = "";

    /**
     * @brief Construct a new Matrix Graph Solution object.
     * 
     */
    MatrixGraphSolution();

    std::string getOutputFileType() const override final;

    std::string getSolutionString(const Problem* problem) const override final;

    void writeToFile(const Problem* problem, const std::string& fileName) const override final;

protected:
    /**
     * @brief The algorithm we use to solve the problem.
     * 
     * @param graph 
     * @return std::string 
     */
    virtual std::string algorithm(const graph::Graph& graph) const = 0;

    /**
     * @brief Initializes the 'steps' matrix to be WAS_NOT_STEPPED.
     * 
     * @param steps - a matrix which indicates if we stepped in cell (x, y)
     */
    static void initialSteps(matrix::MatrixClass& steps);
};

}

}