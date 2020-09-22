#pragma once

#include "Solution.hpp"
#include <iostream>

namespace solver {

namespace string_solution {

class StringSolution : public solver::Solution {
public:
    virtual std::string getSolutionString(const Problem* problem) const;

    bool isStringSolution() const override final;
};

}

}