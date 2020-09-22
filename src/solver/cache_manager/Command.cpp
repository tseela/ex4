#include "Command.hpp"

using namespace std;

solver::cache::Command::Command(const Problem* problem, const Solution* solution) {
    m_problem = problem;
    m_solution = solution;
}

void solver::cache::Command::writeToFile(const std::string& fileName) const { m_solution->writeToFile(m_problem, fileName); }
string solver::cache::Command::getOutputFileType() const { return m_solution->getOutputFileType(); }
string solver::cache::Command::getCacheString() const {
    return m_solution->getCacheCode() + " " + m_solution->getCacheString() + " " + m_problem->getCacheString();
}