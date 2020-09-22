#include "StringFunctions.hpp"

using std::string;
    
string OperatorsHelpingFuncs::copyToString(const char *charArray) {
    string str (charArray);
    return str;
}

bool OperatorsHelpingFuncs::typed(const string& fileName, const string& type) {
    return fileName.substr(fileName.find_last_of('.') + 1).compare(type) == 0;
}