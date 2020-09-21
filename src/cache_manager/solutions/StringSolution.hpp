#pragma once

#include "Solution.hpp"
#include <iostream>

class StringSolution : public Solution {
public:
    virtual std::string getSolutionString(Problem* const problem) const;

    bool isStringSolution() const override final;
};
