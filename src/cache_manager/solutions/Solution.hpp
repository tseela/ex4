#pragma once

#include "Problem.hpp"
#include "StringFunctions.hpp"
#include "file_reading.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

class Solution {
public:
    static constexpr char NOT_INITIALIZED[] = "";
    static constexpr char PRINT[] = "stdout";

    /**
     * @brief Construct a new Solution object.
     * the default constracor- for the sub classes.
     */
    Solution() = default;
    
    /**
     * @brief copy Constructor.
     * 
     * @param op the Solution to copy.
     */
    Solution(const Solution& op);

    /**
     * @brief assignment opperator (copy assignment).
     * 
     * @param op the Solution to copy.
     * @return Solution& the copied Solution.
     */
    Solution& operator=(const Solution& op);

    /**
     * @brief move Constructor.
     * 
     * @param op the Solution to move.
     */
    Solution(Solution&& op);

    /**
     * @brief assignment opperator (move assignment).
     * 
     * @param op the Solution to move.
     * @return Solution& the moved Solution.
     */
    Solution& operator=(Solution&& op);

    /**
     * @brief Get the type of the output file.
     * 
     * @return string 
     */
    virtual std::string getOutputFileType() const = 0;

    /**
     * @brief Get the Cache Code of the object (the begining of the CacheString).
     * 
     * @return string 
     */
    virtual std::string getCacheCode() const = 0;

    /**
     * @brief Writes the result to the output file.
     * 
     */
    void writeToOutputFile(Problem* const problem) const;

    /**
     * @brief Writes to the output file.
     * 
     * @param content - what it will write to the file.
     */
    void writeToOutputFile(Problem* const problem, const std::string& content) const;

    /**
     * @brief Writes the result of the Solution.
     * 
     * @param fileName - the name of the file we write to.
     */
    virtual void writeToFile(Problem* const problem, const std::string& fileName) const = 0;

    virtual bool isStringSolution() const;

    /**
     * @brief Destroy the Solution object.
     * 
     */
    virtual ~Solution() = default;

protected:
    std::string m_outputFilePath = NOT_INITIALIZED; //no output file
};