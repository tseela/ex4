#include "MatrixGraphSolution.hpp"

using namespace std;
using namespace graph;
using namespace solver::problem;

const graph::Graph* getGraph(const solver::Problem* graphProblem);

solver::solution::MatrixGraphSolution::MatrixGraphSolution() {}

string solver::solution::MatrixGraphSolution::getOutputFileType() const { return "txt"; }

void solver::solution::MatrixGraphSolution::writeToFile(const Problem* graphProblem, const string& fileName) const {
    if (fileName == PRINT) {
        cout << getSolutionString(graphProblem) << endl;
    } else {
        files::writeFileContent(fileName, getSolutionString(graphProblem));
    }
}

string solver::solution::MatrixGraphSolution::getSolutionString(const Problem* graphProblem) const {
    auto graph = getGraph(graphProblem);
    return algorithm(*graph);
}

void solver::solution::MatrixGraphSolution::initialSteps(matrix::MatrixClass& steps) {
    for (uint32_t i = 0; i < steps.getHeight(); ++i) {
        for (uint32_t j = 0; j < steps.getWidth(); ++j) {
            steps.setValue(i, j, solver::solution::MatrixGraphSolution::WAS_NOT_STEPPED);
        }
    }
}

const graph::Graph* getGraph(const solver::Problem* graphProblem) {
    // if the casting fails because the problem isn't the one we ecpected to
    // we throw our own exception (which really looks better then the thrown one)
    try {
        auto problem = dynamic_cast<MatrixGraphProblem *>(const_cast<solver::Problem *>(graphProblem));

        // the casting might not throw anything, but it will return us null
        if (problem == nullptr) {
            throw exception();
        }

        return problem->getGraph();

    } catch (const bad_cast& e) {
        throw runtime_error("Error! Solution does not match the problem.");
    }
}