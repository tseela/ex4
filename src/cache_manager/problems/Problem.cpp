#include "Problem.hpp"

using namespace std;

Problem::Problem(const Problem& op) : m_cacheString(op.m_cacheString),
 m_inputFilesPath(op.m_inputFilesPath) {}

Problem& Problem::operator=(const Problem& op) {
    //copying the data
    m_cacheString = op.m_cacheString;
    m_inputFilesPath = op.m_inputFilesPath;

    return *this;
}

Problem::Problem(Problem&& op) : m_cacheString(op.m_cacheString),
 m_inputFilesPath(op.m_inputFilesPath) {
     //copying the data
    m_cacheString = op.m_cacheString;
    m_inputFilesPath = op.m_inputFilesPath;

    // Nulling out the deta of op
   op.m_cacheString = NOT_INITIALIZED;
   op.m_inputFilesPath.clear();
}

Problem& Problem::operator=(Problem&& op) {
    // Nulling out the deta of op
   op.m_cacheString = NOT_INITIALIZED;
   op.m_inputFilesPath.clear();

   return *this;
}