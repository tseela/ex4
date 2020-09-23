#pragma once

#include "MatrixGraphProblem.hpp"
#include "Solution.hpp"
#include <iostream>

namespace solver {

class MatrixGraphSolution : public solver::Solution {
public:
    MatrixGraphSolution();

    std::string getOutputFileType() const override;

    std::string getCacheCode() const override;

    std::string getSolutionString(const Problem* problem) const override;

    void writeToFile(const Problem* problem, const std::string& fileName) const override;

private:
    virtual std::string algorithm(graph::Graph);
};

}