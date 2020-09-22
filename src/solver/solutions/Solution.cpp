#include "Solution.hpp"

using namespace std;

solver::Solution::Solution(const Solution& op) : m_outputFilePath(op.m_outputFilePath){}

solver::Solution& solver::Solution::operator=(const Solution& op) {
    // copying the data
    m_outputFilePath = op.m_outputFilePath;

    return *this;
}

solver::Solution::Solution(Solution&& op) : m_outputFilePath(op.m_outputFilePath){
    // copying the data
    m_outputFilePath = op.m_outputFilePath;

    // Nulling out the deta of op
   op.m_outputFilePath = NOT_INITIALIZED;
}

solver::Solution& solver::Solution::operator=(Solution&& op) {

    // Nulling out the deta of op
   op.m_outputFilePath = NOT_INITIALIZED;

   return *this;
}

void solver::Solution::writeToOutputFile(const Problem* problem) const {
    if (m_outputFilePath.compare(NOT_INITIALIZED) == 0) {//no output file
        return;
    }
    writeToFile(problem, m_outputFilePath);
}

void solver::Solution::writeToOutputFile(const Problem* problem, const string& content) const {
    if (m_outputFilePath.compare(NOT_INITIALIZED) == 0) {//no output file
        return;
    }
    if (!m_outputFilePath.compare(PRINT)) {//if output is stdout
        cout << content << endl;
    } else {
        writeFileContent(m_outputFilePath, content);
    }
}

bool solver::Solution::isStringSolution() const { return false; }

string solver::Solution::getCacheString() const { return ""; }