#include "Solution.hpp"

using namespace std;

Solution::Solution(const Solution& op) : m_outputFilePath(op.m_outputFilePath){}

Solution& Solution::operator=(const Solution& op) {
    // copying the data
    m_outputFilePath = op.m_outputFilePath;

    return *this;
}

Solution::Solution(Solution&& op) : m_outputFilePath(op.m_outputFilePath){
    // copying the data
    m_outputFilePath = op.m_outputFilePath;

    // Nulling out the deta of op
   op.m_outputFilePath = NOT_INITIALIZED;
}

Solution& Solution::operator=(Solution&& op) {

    // Nulling out the deta of op
   op.m_outputFilePath = NOT_INITIALIZED;

   return *this;
}

void Solution::writeToOutputFile(Problem* const problem) const {
    if (m_outputFilePath.compare(NOT_INITIALIZED) == 0) {//no output file
        return;
    }
    writeToFile(problem, m_outputFilePath);
}

void Solution::writeToOutputFile(Problem* const problem, const string& content) const {
    if (m_outputFilePath.compare(NOT_INITIALIZED) == 0) {//no output file
        return;
    }
    if (!m_outputFilePath.compare(PRINT)) {//if output is stdout
        cout << content << endl;
    } else {
        writeFileContent(m_outputFilePath, content);
    }
}

bool Solution::isStringSolution() const {
    return false;
}
