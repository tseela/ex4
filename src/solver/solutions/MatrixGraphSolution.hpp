#pragma once

#include "MatrixGraphProblem.hpp"
#include "Solution.hpp"
#include <iostream>

namespace solver {

namespace solution {

class MatrixGraphSolution : public solver::Solution {
public:
    static constexpr auto WAS_STEPPED = 1;
    static constexpr auto WAS_NOT_STEPPED = 0;

    MatrixGraphSolution();

    std::string getOutputFileType() const override final;

    std::string getCacheCode() const override final;

    std::string getSolutionString(const Problem* problem) const override final;

    void writeToFile(const Problem* problem, const std::string& fileName) const override final;

protected:
    virtual std::string algorithm(const graph::Graph& graph) const;

    static void initialSteps(matrix::MatrixClass& steps);
};

}

}