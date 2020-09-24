#include "MatrixClass.hpp"
#include "BFS.hpp"
#include "DFS.hpp"
#include "AStar.hpp"
#include "MatrixGraphProblem.hpp"
#include "Solver.hpp"
#include "BestFS.hpp"
#include <memory>

using namespace std;
using namespace matrix;
using namespace graph;
using namespace solver;
using namespace solver::solution;

void initializeMatrix(matrix::MatrixClass* matrix) {
    for (uint32_t i = 0; i < matrix->getHeight(); ++i) {
        for (uint32_t j = 0; j < matrix->getWidth(); ++j) {
            matrix->setValue(i, j, (rand() % 99) + 1);
        }
    }
}

int getCost(const string& line) {
    auto a = line.find_first_of(',') - 1;
    auto b = line.substr(0, a);
    auto c = b.c_str();
    auto d = atoi(c);
    return d;
}

int numOfSteps(const std::string& input) {
	int iSpaces = 0;

	for (auto i = 0; i < (int) input.length(); ++i) {
		if (input[i] == ',') { ++iSpaces; }
    }

	return iSpaces - 2;
}

int main() {
    try {
    string s = "";
    string s1[4] = {"", "", "", ""};
    string s2[4] = {"", "", "", ""};
    auto dfs = new graph_solution::DFS();
    auto bfs = new graph_solution::BFS();
    auto a_star = new graph_solution::AStar();
    auto best = new graph_solution::BestFS();
    vector<Solver *> solvers;

    for (auto i = 0; i < 500; ++i) {

        auto x = (rand() % 96) + 5;
        auto y = (rand() % 96) + 5;
        auto size = x * y;

        auto matrix = new matrix::MatrixClass(x, y);
        initializeMatrix(matrix);

        s += to_string(x) + "," + to_string(y) + "\n" + matrix->toString() + "\n\n";

        auto p = new problem::MatrixGraphProblem(matrix, 0, 0, matrix->getHeight() - 1, matrix->getWidth() - 1);

        solvers.push_back(new Solver(p, dfs));
        solvers.push_back(new Solver(p, bfs));
        solvers.push_back(new Solver(p, a_star));
        solvers.push_back(new Solver(p, best));

        for (auto j = static_cast<int>(solvers.size()) - 1; j > 0;) {
            s1[j] += to_string(numOfSteps(solvers[j]->getStringSolution(false))) + "," + to_string(size) + "\n";
            s2[j] += to_string(getCost(solvers[j]->getStringSolution(false))) + "," + to_string(size) + "\n";
            solvers.pop_back();
        }
    }

    files::writeFileContent("matrices.txt", s);
    files::writeFileContent("dfs_1.txt", s1[0]);
    files::writeFileContent("dfs_2.txt", s2[0]);
    files::writeFileContent("bfs_1.txt", s1[1]);
    files::writeFileContent("bfs_2.txt", s2[1]);
    files::writeFileContent("Astar_1.txt", s1[2]);
    files::writeFileContent("Astar_2.txt", s2[2]);
    files::writeFileContent("best_1.txt", s1[3]);
    files::writeFileContent("best_2.txt", s2[3]);
    } catch (matrix::ErrorCodeException e) {
        e.printErrorMessage();
    }
}