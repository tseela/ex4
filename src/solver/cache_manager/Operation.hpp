#pragma once

#include "Problem.hpp"
#include "Solution.hpp"

namespace solver {

namespace cache {

class Operation {
public:
    /**
     * @brief Construct a new Operation object.
     * 
     * @param problem 
     * @param solution 
     */
    Operation(const Problem* problem, const Solution* solution);

    /**
     * @brief Writes the solution to the file.
     * 
     * @param fileName 
     */
    void writeToFile(const std::string& fileName) const;
    /**
     * @brief Gets the type of the output file object.
     * 
     * @return std::string 
     */
    std::string getOutputFileType() const;
    /**
     * @brief Gets the Cache String of the object (the line we write in the cache).
     * 
     * @return std::string 
     */
    std::string getCacheString() const;

private:
    const Problem* m_problem;
    const Solution* m_solution;
};

}

}