#pragma once

#include "file_reading.hpp"
#include "CurrentTime.hpp"
#include "Operation.hpp"

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <filesystem>
#include <errno.h>
#include <system_error>

class Operation;

/**
 * @brief this class stands for the cache.
 */
class CacheManager {
public:
    static constexpr char CACHE_FILE[] = "src/bin/cache/Cache__DONT_TOUCH_THIS_FILE.txt";
    static constexpr char CACHE_LINE[] = "Cache Manager is running!\n";
    static constexpr char CACHE_DIR[] = "src/bin/cache";
    static constexpr char CACHE_FILES_DIR[] = "src/bin/cache/files";
    static constexpr char CACHE_FILES_DIR_[] = "src/bin/cache/files/";

    static constexpr int CACHE_LINE_LENGTH = 26;

    /**
     * @brief Construct a new Cache Manager object.
     * 
     * @param op the operation that is given.
     */
    CacheManager(std::unique_ptr<Operation>& op);

    /**
     * @brief Does an operation.
     * 
     * @param operation - the operation.
     * @param isSearched - is the operation is searched or not.
     * @param isClear - if the operation is clear or not.
     */
    void performOperation(bool isSearched = false, bool isClear = false) const;

    /**
     * @brief Search an operation in the cache.
     * 
     * @param operation
     * @return string 
     */
    std::string search() const;

    /**
     * @brief Checks if a command is search operation.
     * 
     * @param argc the num of words in the command.
     * @param argv the command.
     * @return true if the operation is search, else false.
     */
    static bool isSearch(int argc, const char* argv[]);

    /**
     * @brief Checks if a command is clear operation.
     * 
     * @param argc the num of words in the command.
     * @param argv the command.
     * @return true if the operation is clear, else false. 
     */
    static bool isClear(int argc, const char* argv[]);

private:
    std::unique_ptr<Operation> _operation;
};