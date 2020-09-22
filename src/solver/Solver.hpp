#include "CacheManager.hpp"
#include "StringSolution.hpp"

namespace server_side {
    class Solver {
        public:
            Solver(const Problem* problem, const Solution* solution);

            std::string getStringSolution() const;

        private:
            const Problem* m_problem;
            const Solution* m_solution;
    };
};