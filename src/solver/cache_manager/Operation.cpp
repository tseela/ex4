#include "Operation.hpp"

using namespace std;

solver::cache::Operation::Operation(const Problem* problem, const Solution* solution) {
    m_problem = problem;
    m_solution = solution;
}

void solver::cache::Operation::writeToFile(const std::string& fileName) const { m_solution->writeToFile(m_problem, fileName); }

string solver::cache::Operation::getOutputFileType() const { return m_solution->getOutputFileType(); }

string solver::cache::Operation::getCacheString() const {
    return m_solution->getCacheCode() + " " + m_solution->getCacheString() + " " + m_problem->getCacheString();
}