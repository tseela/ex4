#include "BestPath.hpp"

BestPath::BestPath() {
    bestCost = NOT_FOUND;
    bestPath = "";
}

BestPath::BestPath(const double cost, const std::string& path) {
    bestCost = cost;
    bestPath = path;
}