#pragma once

#include "Solution.hpp"
#include <iostream>

class MatrixGraphDFS : public Solution {
public:
    std::string getOutputFileType() const;

    std::string getCacheCode() const;

    void writeToFile(Problem* problem, const std::string& fileName) const;
};
