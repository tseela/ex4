#pragma once

#include <string>

/**
 * @brief A struct with cost & path (for the solution of the matrix graph problem).
 * 
 */
struct BestPath {
    static constexpr auto NOT_FOUND = -1;

    double bestCost;
    std::string bestPath;

    /**
     * @brief Construct a new Best Path object which repressents a path that wasn't found.
     * 
     */
    BestPath();

    /**
     * @brief Construct a new Best Path object.
     * 
     * @param cost 
     * @param path 
     */
    BestPath(const double cost, const std::string& path);
};