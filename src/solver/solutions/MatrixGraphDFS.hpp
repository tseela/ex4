#pragma once

#include "StringSolution.hpp"
#include "MatrixGraphProblem.hpp"
#include <iostream>

namespace solver {

namespace string_solution {

class MatrixGraphDFS : public solver::string_solution::StringSolution {
public:
    std::string getOutputFileType() const override;

    std::string getCacheCode() const override;

    std::string getCacheString() const override;

    std::string getSolutionString(const Problem* problem) const override;

    void writeToFile(const Problem* problem, const std::string& fileName) const override;
};

}

}