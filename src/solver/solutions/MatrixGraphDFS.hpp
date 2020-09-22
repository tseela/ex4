#pragma once

#include "StringSolution.hpp"
#include "MatrixGraphProblem.hpp"
#include <iostream>

class MatrixGraphDFS : public StringSolution {
public:
    std::string getOutputFileType() const override;

    std::string getCacheCode() const override;

    std::string getCacheString() const override;

    std::string getSolutionString(Problem* const problem) const override;

    void writeToFile(Problem* const problem, const std::string& fileName) const override;
};
