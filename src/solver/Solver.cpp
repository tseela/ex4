#include "Solver.hpp"

using namespace std;
using namespace solver::cache;

solver::Solver::Solver(const Problem* problem, const Solution* solution) {
    m_problem = problem;
    m_solution = solution;
}

string solver::Solver::getStringSolution() const {
    // if the cache codes of the two doesn't match we can't activate the solution on the problem.
    if (m_problem->getCacheCode().compare(m_solution->getCacheCode()) != 0) {
        throw runtime_error("Problem & Solution doesn't match!");
    }
    
    auto command = Operation(m_problem, m_solution);
    auto cache = CacheManager();
    cache.saveInCache(command);

    // if there isn't a backup file for this problem's solution we will solve it:
    if (cache.getBackUpFile(command).compare("") == 0) {
        return m_solution->getSolutionString(m_problem);
    }

    // else, we return the backup file's content.
    return files::readFileContent(cache.getBackUpFile(command));
}