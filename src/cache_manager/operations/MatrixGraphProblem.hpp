#pragma once

#include "crc32FileReader.hpp"
#include "Problem.hpp"
#include "MatrixClass.hpp"

#include <string>
#include <memory>

/**
 * @brief This class stands for the "matrix mult" Problem.
 */
class MatrixGraphProblem : public Problem {
public:
    MatrixGraphProblem(const MatrixClass& matrix);
    
    string getCacheCode() const override;

    string getCacheString() const override;

    MatrixClass getGraph() const;

private:
    unique_ptr<MatrixClass> graph;
};