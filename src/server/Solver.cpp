#include "Solver.hpp"

using namespace std;

server_side::Solver::Solver(const Problem* problem, const Solution* solution) {
    m_problem = problem;
    m_solution = solution;
}

string server_side::Solver::getStringSolution() const {
    // we can't return the string of the solution if our solution isn't a string solution...
    if (!m_solution->isStringSolution()) {
        throw runtime_error("You can't get a string from this solution!");
    }

    // if the cache codes of the two doesn't match we can't activate the solution on the problem.
    if (m_problem->getCacheCode().compare(m_solution->getCacheCode()) != 0) {
        throw runtime_error("Problem & Solution doesn't match!");
    }
    
    auto solution = dynamic_cast<StringSolution *>(const_cast<Solution *>(m_solution));

    auto command = Command(m_problem, solution);
    auto cache = CacheManager();
    cache.saveInCache(command);

    // if there isn't a backup file for this problem's solution we will solve it:
    if (cache.getBackUpFile(command).compare("") == 0) {
        return solution->getSolutionString(m_problem);
    }

    // else, we return the backup file's content.
    return readFileContent(cache.getBackUpFile(command));
}