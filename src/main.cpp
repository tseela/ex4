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

void initializeMatrix(matrix::MatrixClass* matrix, const int x) {
    auto b = x / 7 + 10;
    for (uint32_t i = 0; i < matrix->getHeight(); ++i) {
        for (uint32_t j = 0; j < matrix->getWidth(); ++j) {
            matrix->setValue(i, j, rand() % b + 1);
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
    string s1 = "";
    string s2 = "";
    auto dfs = new graph_solution::DFS();
    auto bfs = new graph_solution::BFS();
    auto a_star = new graph_solution::AStar();
    auto best = new graph_solution::BestFS();
    vector<Solver *> solvers;

    for (auto i = 0; i < 500; ++i) {
        
        cout << i << endl;

        auto x = (rand() % 96) + 5;
        auto y = (rand() % 96) + 5;
        auto size = x * y;

        auto matrix = new matrix::MatrixClass(x, y);
        initializeMatrix(matrix, i);

        s += to_string(x) + "," + to_string(y) + "\n" + matrix->toString() + "\n\n";

        auto p = new problem::MatrixGraphProblem(matrix, 0, 0, matrix->getHeight() - 1, matrix->getWidth() - 1);

        solvers.push_back(new Solver(p, dfs));
        solvers.push_back(new Solver(p, bfs));
        solvers.push_back(new Solver(p, a_star));
        solvers.push_back(new Solver(p, best));

        s1 += to_string(size) + ",,";
        for (auto j = static_cast<int>(solvers.size()) - 1; j >= 0; --j) {
            s1 += to_string(numOfSteps(solvers[j]->getStringSolution())) + ",";
            s2 += to_string(getCost(solvers[j]->getStringSolution())) + ",";
            solvers.pop_back();
        }
        s1 += "\n";
        s2 += "\n";
    }
    files::writeFileContent("matrices.txt", s);
    files::writeFileContent("1.txt", s1);
    files::writeFileContent("2.txt", s2);
    } catch (matrix::ErrorCodeException e) {
        e.printErrorMessage();
    }
}