#pragma once

#include "Solution.hpp"
#include <iostream>

class StringSolution : public Solution {
public:
    virtual std::string getSolutionString(const Problem* problem) const;

    bool isStringSolution() const override final;
};
