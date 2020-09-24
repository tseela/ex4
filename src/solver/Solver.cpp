#include "Solver.hpp"

using namespace std;
using namespace solver::cache;

solver::Solver::Solver(const Problem* problem, const Solution* solution) {
    m_problem = problem;
    m_solution = solution;
}

string solver::Solver::getStringSolution(bool useCache /*= true*/) const {
    if (useCache) {
        auto cache = CacheManager();
        auto command = Operation(m_problem, m_solution);
        cache.saveInCache(command);

        // if there is a backup file for this problem's solution, we will return it's content
        if (cache.getBackUpFile(command).compare("") != 0) {
            return files::readFileContent(cache.getBackUpFile(command));
        }
    }

    // if we don't use the cache manager we will solve the problem ourselves.
    return m_solution->getSolutionString(m_problem);
}