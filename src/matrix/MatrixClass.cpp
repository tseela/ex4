#include "MatrixClass.hpp"

//Implementing methods
	MatrixClass::MatrixClass(uint32_t height, uint32_t width){
        //creating the matrix & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(matrix_create(&_matrix, height, width));
    }

    MatrixClass::MatrixClass(const MatrixClass& source){
        //copy the matrix & throwing excepstion if needed
        ErrorCodeException::throwErrorIfNeeded(matrix_copy(&_matrix, source._matrix));
    }

    MatrixClass::MatrixClass(const string& filePath) {
        //opening the file
        ifstream matrixFile;
        matrixFile.open(filePath);
        if (matrixFile.fail()) {
            throw std::system_error(errno, std::system_category());
        }
        
        // checking if the file is empty
        if (matrixFile.peek() == std::ifstream::traits_type::eof()) {
            matrixFile.close();
            throw std::runtime_error("The file in empty. Can not convert into matrix.");
        }

        //helping varibles
        string line;
        u_int32_t numOfRow = 0;
        u_int32_t numOfCol = 0;

    //checking how many rows & colums in the matrix
        getline(matrixFile,line);
        numOfRow++; //the first row

        //num of cols
        for (auto c: line) {
		    if(c == ',') {
                ++numOfCol;
            }
        }

        //the num of ',' is 1 less than the num of col in the matrix
        ++numOfCol;
        
        //continue calculating the height of the matrix
        while (getline(matrixFile, line)) {
            ++numOfRow;
        }
    //end checking how many rows & colums in the matrix
        
        //creating the matrix & throwing exception if needed
        try {
            ErrorCodeException::throwErrorIfNeeded(matrix_create(&_matrix, numOfRow, numOfCol));
        } catch (const ErrorCodeException& e){
            matrixFile.close();
            throw e;
        }

        //setting the file
        matrixFile.clear();
        matrixFile.seekg(0);

        //Intlizing the matrix
        for (u_int32_t row = 0; getline(matrixFile, line); ++row) {
            //removing spaces
            line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

            //helping varibles
            u_int32_t col = 0;
            string valueInString = "";
            u_int32_t numOfValuesPerRow = 0;
            
            for (auto c: line) {
		        if (c == ',') {
                    //setting the value
                    if(valueInString == "") {
                        matrix_destroy(_matrix);
                        matrixFile.close();
                        throw std::runtime_error("Found a ',' without a number before it. Can not convert into matrix.");
                    }

                    //setting var
                    try{
                        ErrorCodeException::throwErrorIfNeeded(
                        matrix_setValue(_matrix, row, col, stod(valueInString)));
                        ++numOfValuesPerRow;
                    } catch (const ErrorCodeException& e){
                        matrix_destroy(_matrix);
                        matrixFile.close();
                        throw e;
                    }

                    valueInString = "";
                    ++col;
                    continue;
                }

                // if we reached an unknown character
                if (c != '.' && c != '-' && !(c >= '0' && c <= '9')) {
                    matrix_destroy(_matrix);
                    matrixFile.close();
                    throw std::runtime_error("Found an unknown character in the file. Can not convert into matrix.");
                }

                valueInString += c;

                // if we read two character in a number and both are not digits
                if (valueInString.length() > 1 &&
                !(valueInString[valueInString.length() - 1] >= '0' &&
                 valueInString[valueInString.length() - 1] <= '9') &&
                !(valueInString[valueInString.length() - 2] >= '0' &&
                 valueInString[valueInString.length() - 2] <= '9')) {
                    matrix_destroy(_matrix);
                    matrixFile.close();
                    throw std::runtime_error("Found unknown combination on characters. Can not convert into matrix.");
                }
            }
            //setting the value of the last index in the line
            if(valueInString == "") {
                matrix_destroy(_matrix);
                matrixFile.close();
                throw std::runtime_error("Found a ',' without a number after it. Can not convert into matrix.");
            }

            // if we read two character in a number and both are not digits
            if (valueInString.length() > 1 &&
            !(valueInString[valueInString.length() - 1] >= '0' &&
             valueInString[valueInString.length() - 1] <= '9') &&
            !(valueInString[valueInString.length() - 2] >= '0' &&
            valueInString[valueInString.length() - 2] <= '9')) {
                matrix_destroy(_matrix);
                matrixFile.close();
                throw std::runtime_error("Found unknown combination on characters. Can not convert into matrix.");
            }
            
            try{
                ErrorCodeException::throwErrorIfNeeded(
                matrix_setValue(_matrix, row, col, stod(valueInString)));
                ++numOfValuesPerRow;
            }catch (const ErrorCodeException& e){
                matrix_destroy(_matrix);
                matrixFile.close();
                throw e;
            }

            if(numOfValuesPerRow < numOfCol){
                matrix_destroy(_matrix);
                matrixFile.close();
                throw std::runtime_error("Found a raw with less values than needed");
            }
        }
        matrixFile.close();
    }

    MatrixClass& MatrixClass::operator=(const MatrixClass& source){

        //Trying to destroy the matrix in the field (if not intalized yet would do nothing)
        matrix_destroy(_matrix);

        //creating copy of the matrix in the field & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(matrix_copy(&_matrix, source._matrix));

        return *this;
    }

    uint32_t MatrixClass::getHeight() const {
        uint32_t height;

        //gets the height & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(matrix_getHeight(_matrix, &height));

        return height;
    }

    uint32_t MatrixClass::getWidth() const {
        uint32_t width;

        //gets the width & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(matrix_getWidth(_matrix, &width));

        return width;
    }

    void MatrixClass::setValue(uint32_t rowIndex, uint32_t colIndex,
                           double value) {
        //sets the value & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(
            matrix_setValue(_matrix, rowIndex, colIndex, value));
    }

    double MatrixClass::operator()(uint32_t rowIndex, uint32_t colIndex) const{
        double value;

        //gets the value & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(
            matrix_getValue(_matrix, rowIndex, colIndex, &value));

        return value;
    }

    MatrixClass& MatrixClass::operator+=(const MatrixClass& other) {
        //Creating the result matrix 
        PMatrix result;
        matrix_create(&result, this->getHeight(), this->getWidth());

        //Calculating result matrix & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(
            matrix_add(&result, _matrix, other._matrix));

        //destroying the corrent matrix
        matrix_destroy(_matrix);

        //updating the matrix to the result
        _matrix = result;

        return *this;
    }

    MatrixClass&  MatrixClass::operator-=(const MatrixClass& other) {
        MatrixClass* minusOther = &(other * (-1));
        (*this) += *minusOther;
        delete minusOther;
        return *this;
    }

    MatrixClass& MatrixClass::operator*=(const MatrixClass& other) {
        //Creating the result matrix 
        PMatrix result;
        matrix_create(&result, this->getHeight(), other.getWidth());

        //Calculating result matrix & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(
            matrix_multiplyMatrices(&result, _matrix, other._matrix));

        //destroying the corrent matrix
        matrix_destroy(_matrix);

        //updating the matrix to the result
        _matrix = result;

        return *this;
    }

    MatrixClass& MatrixClass::operator*=(double scalar){
        //Multipling this matrix with the scalar into 
        //this matrix & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(
            matrix_multiplyWithScalar(_matrix, scalar));

        return *this;
    }

    MatrixClass& MatrixClass::operator/=(double scalar) {
        return *(this) *= (1 / scalar);
    }

    MatrixClass::~MatrixClass() {
        //destroying the corrent matrix
        matrix_destroy(_matrix);
    }

//another operators. warning! they return new MatrixClass
    MatrixClass& MatrixClass::operator+(const MatrixClass& other) const{
        //Creating the result matrix 
        MatrixClass* result = new MatrixClass(this->getHeight(), this->getWidth());

        //Calculating result matrix & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(
            matrix_add(&result->_matrix, _matrix, other._matrix));

        return *result;
    }

    MatrixClass& MatrixClass::operator-(const MatrixClass& other) const {
        MatrixClass* minusOther = &(other * (-1));
        MatrixClass* result = &((*this) + *minusOther);
        delete minusOther;
        return *result;
    }

    MatrixClass& MatrixClass::operator*(const MatrixClass& other) const{
        //Creating the result matrix 
        MatrixClass* result = new MatrixClass(this->getHeight(), other.getWidth());

        //Calculating result matrix & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(
            matrix_multiplyMatrices(&result->_matrix, _matrix, other._matrix));

        return *result;
    }

    MatrixClass& MatrixClass::operator*(double scalar) const {
        //Creating the result matrix (copying this matrix)
        MatrixClass* result = new MatrixClass(*this);

        //Multipling this matrix with the scalar into 
        //this matrix & throwing exception if needed
        ErrorCodeException::throwErrorIfNeeded(
            matrix_multiplyWithScalar(result->_matrix, scalar));

        return *result;
    }

    MatrixClass& MatrixClass::operator/(double scalar) const {
        return *this * (1 / scalar);
    }

    string MatrixClass::toString() const{
        //var to use
        uint32_t height = getHeight();
        uint32_t width = getWidth();

        string s = "";
        for(uint32_t row = 0; row < height; ++row) {
            for(uint32_t col = 0; col < width - 1; ++col) { //to all the middle values.
                s+= std::to_string((*this)(row, col)) + ",";
            }
        //to the end of the row values
        //must be one because the size of the matrix are positive
        s +=  std::to_string((*this)(row, width - 1));

        if(row != height -1) {
            s += "\n";
        }
        }
        return s;
    }

//friends functins
    std::ostream& operator<<(std::ostream& stream, const MatrixClass& matrix){
        //var to use
        uint32_t height = matrix.getHeight();
        uint32_t width = matrix.getWidth();

        for(uint32_t row = 0; row < height; ++row) {
            for(uint32_t col = 0; col < width - 1; ++col) { //to all the middle values.
                stream<<matrix(row, col)<<",";
            }
        //to the end of the row values
        //must be one because the size of the matrix are positive
        stream<<matrix(row, width - 1);

        stream<<endl;
        }

        return stream;
    }

    MatrixClass& operator*(double scalar, const MatrixClass& matrix) {
        return matrix * scalar;
    }
