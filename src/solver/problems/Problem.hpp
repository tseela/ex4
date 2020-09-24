#pragma once

#include "file_reading.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

#define NUMBER_OF_ARGUMENTS_ERROR std::runtime_error("Invalid input! Number of arguments does not suit to the chosen Problem.")
#define UNKNOWN_COMMAND std::runtime_error("Invalid input! Unknown command.")

namespace solver {

/**
 * @brief this class represent one Problem.
 * 
 */
class Problem {
public:
    static constexpr int START_INDEX = 0;
    static constexpr auto NOT_INITIALIZED = "";

    /**
     * @brief Construct a new Problem object.
     * the default constracor- for the sub classes.
     */
    Problem() = default;
    
    /**
     * @brief copy Constructor.
     * 
     * @param op the Problem to copy.
     */
    Problem(const Problem& op);

    /**
     * @brief assignment opperator (copy assignment).
     * 
     * @param op the Problem to copy.
     * @return Problem& the copied Problem.
     */
    Problem& operator=(const Problem& op);

    /**
     * @brief move Constructor.
     * 
     * @param op the Problem to move.
     */
    Problem(Problem&& op);

    /**
     * @brief assignment opperator (move assignment).
     * 
     * @param op the Problem to move.
     * @return Problem& the moved Problem.
     */
    Problem& operator=(Problem&& op);

    /**
     * @brief Get the Cache Code of the object (the begining of the CacheString).
     * 
     * @return string 
     */
    virtual std::string getCacheCode() const = 0;

    /**
     * @brief Get the Cache String of the object (what we write on our cache file).
     * 
     * @return string 
     */
    virtual std::string getCacheString() const = 0;

    /**
     * @brief Destroy the Problem object.
     * 
     */
    virtual ~Problem() = default;

protected:
    std::string m_cacheString = NOT_INITIALIZED;
    std::vector<std::string> m_inputFilesPath;
};

}