#pragma once

#include "StringFunctions.hpp"
#include "file_reading.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

#define NUMBER_OF_ARGUMENTS_ERROR std::runtime_error("Invalid input! Number of arguments does not suit to the chosen operation.")
#define UNKNOWN_COMMAND std::runtime_error("Invalid input! Unknown command.")

/**
 * @brief this class represent one operation in the cache
 * that is not cache operation. But it could be uses
 * to represent a part of a search operation that would
 * represent the operation we are locking for.
 */
class Operation {
public:
    static constexpr int START_INDEX = 0;
    static constexpr char PRINT[] = "stdout";
    static constexpr char NOT_INITIALIZED[] = "";

    /**
     * @brief Construct a new Operation object.
     * the default constracor- for the sub classes.
     */
    Operation() = default;
    
    /**
     * @brief copy Constructor.
     * 
     * @param op the Operation to copy.
     */
    Operation(const Operation& op);

    /**
     * @brief assignment opperator (copy assignment).
     * 
     * @param op the operation to copy.
     * @return Operation& the copied operation.
     */
    Operation& operator=(const Operation& op);

    /**
     * @brief move Constructor.
     * 
     * @param op the Operation to move.
     */
    Operation(Operation&& op);

    /**
     * @brief assignment opperator (move assignment).
     * 
     * @param op the operation to move.
     * @return Operation& the moved operation.
     */
    Operation& operator=(Operation&& op);

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
     * @brief Get the Cache String of the object (what we write on our cache file).
     * 
     * @return string 
     */
    virtual std::string getCacheString() const = 0;

    /**
     * @brief Writes the result to the output file.
     * 
     */
    void writeToOutputFile() const;

    /**
     * @brief Writes to the output file.
     * 
     * @param content - what it will write to the file.
     */
    void writeToOutputFile(const std::string& content) const;

    /**
     * @brief Writes the result of the operation.
     * 
     * @param fileName - the name of the file we write to.
     */
    virtual void writeToFile(const std::string& fileName) const = 0;

    /**
     * @brief Destroy the Operation object.
     * 
     */
    virtual ~Operation() = default;

protected:
    std::string _cacheString = NOT_INITIALIZED;
    std::vector<std::string> _inputFilesPath;
    std::string _outputFilePath = NOT_INITIALIZED;//no output file
};