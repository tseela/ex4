#pragma once

#include "MatrixGraphProblem.hpp"
#include "Solution.hpp"
#include <iostream>

namespace solver {

class MatrixGraphDFS : public solver::Solution {
public:
    MatrixGraphDFS();

    std::string getOutputFileType() const override;

    std::string getCacheCode() const override;

    std::string getCacheString() const override;

    std::string getSolutionString(const Problem* problem) const override;

    void writeToFile(const Problem* problem, const std::string& fileName) const override;
};

}