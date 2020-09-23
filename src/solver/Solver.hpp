#include "CacheManager.hpp"

namespace solver {
    class Solver {
        public:
            Solver(const Problem* problem, const Solution* solution);

            std::string getStringSolution() const;

        private:
            const Problem* m_problem;
            const Solution* m_solution;
    };
}