#pragma once

#include "CacheManager.hpp"
#include "Problem.hpp"
#include "Solution.hpp"

namespace solver {

namespace cache {

class Command {
public:
    Command(const Problem* problem, const Solution* solution);

    void writeToFile(const std::string& fileName) const;
    std::string getOutputFileType() const;
    std::string getCacheString() const;

private:
    const Problem* m_problem;
    const Solution* m_solution;
};

}

}