#include "Operation.hpp"

using namespace std;

Operation::Operation(const Operation& op) : _cacheString(op._cacheString),
 _inputFilesPath(op._inputFilesPath), _outputFilePath(op._outputFilePath){}

Operation& Operation::operator=(const Operation& op) {
    //copying the data
    _cacheString = op._cacheString;
    _inputFilesPath = op._inputFilesPath;
    _outputFilePath = op._outputFilePath;

    return *this;
}

Operation::Operation(Operation&& op) : _cacheString(op._cacheString),
 _inputFilesPath(op._inputFilesPath), _outputFilePath(op._outputFilePath){
     //copying the data
    _cacheString = op._cacheString;
    _inputFilesPath = op._inputFilesPath;
    _outputFilePath = op._outputFilePath;

    // Nulling out the deta of op
   op._cacheString = NOT_INITIALIZED;
   op._inputFilesPath.clear();
   op._outputFilePath = NOT_INITIALIZED;
}

Operation& Operation::operator=(Operation&& op) {

    // Nulling out the deta of op
   op._cacheString = NOT_INITIALIZED;
   op._inputFilesPath.clear();
   op._outputFilePath = NOT_INITIALIZED;

   return *this;
}

void Operation::writeToOutputFile() const {
    if(_outputFilePath.compare(NOT_INITIALIZED) == 0) {//no output file
        return;
    }
    writeToFile(_outputFilePath);
}

void Operation::writeToOutputFile(const string& content) const {
    if(_outputFilePath.compare(NOT_INITIALIZED) == 0) {//no output file
        return;
    }
    if (!_outputFilePath.compare(PRINT)) {//if output is stdout
        cout << content << endl;
    } else {
        writeFileContent(_outputFilePath, content);
    }
}