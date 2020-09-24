#pragma once
#include "Matrix.h"
#include "ErrorCodeException.hpp"

#include <errno.h>
#include <string>
#include <cstdint>
#include <fstream>
#include <algorithm>

using std::uint32_t;
using std::string;
using std::ifstream;

namespace matrix {

class MatrixClass{
//Fields
PMatrix m_matrix;

//methods
public:
	/**
	 * @brief Constructor, all values are initially zeroes.
	 *
	 * @param[in] height Height of the matrix.
	 * @param[in] width Width of the matrix.
	 */
	MatrixClass(uint32_t height, uint32_t width);

	/**
	 * @brief Constructor, a new Matrix Class object from matrix.
	 * (copy Constructor)
	 * 
	 * @param[in] source The matrix to copy.
	 */
	MatrixClass(const MatrixClass& source);

	/**
	 * @brief Constructor, a new Matrix Class object from file.txt
	 * that contains a matrix.
	 * (copy Constructor)
	 * 
	 * @param[in] source The matrix to copy.
	 */
	MatrixClass(const string& filePath);

	/**
	 * @brief assignment opperator (copy assignment).
	 *
	 * @param[in] source The assigned matrix.
	 */
	MatrixClass& operator=(const MatrixClass& source);

	/**
	 * @brief Returns height of given matrix.
	 *
	 * @return uint32_t
	 */
	uint32_t getHeight() const;

	/**
	 * @brief Returns width of matrix.
	 *
	 * @return uint32_t
	 */
	uint32_t getWidth() const;

	/**
	 * @brief Sets a value to the matrix.
	 *******we wished to implement this by operator () but couldn't
	 *******because the functions we used didnt support returning double&
	 * @param[in] rowIndex Row index of the value to set.
	 * @param[in] colIndex Column index of the value to setF.
	 * @param[in] value Value to set.
	 */
	void setValue(uint32_t rowIndex, uint32_t colIndex,
                           double value);

	/**
	 * @brief gets a value to the matrix.
	 *
	 * @param[in] rowIndex Row index of the value to get.
	 * @param[in] colIndex Column index of the value to get.
	 * @return double.
	 */
	double operator()(uint32_t rowIndex, uint32_t colIndex) const;

	/**
	 * @brief Addition opperator (adds to the left side the right side 
	 * (this matrix chenges)).
	 *
	 * @param[in] other The right hand side of the addition operation.
	 * @return MatrixClass& this matrix
	 */
	MatrixClass& operator+=(const MatrixClass& other);

	/**
	 * @brief Minus opperator (reducing the left side by the right side 
	 * (this matrix chenges)).
	 *
	 * @param[in] other The right hand side of the addition operation.
	 * @return MatrixClass& this matrix
	 */
	MatrixClass& operator-=(const MatrixClass& other);

	/**
	 * @brief Multiplication opperator (matrix by matrix the risult in the left matrix(this)).
	 *
	 * @param[in] other The right hand side of the multiplication operation.
	 * @return MatrixClass& this matrix
	 */
	MatrixClass& operator*=(const MatrixClass& other);

	/**
	 * @brief Multiplication operator (matrix by scalar the result in this matrix).
	 *
	 * @param[in] scalar The scalar to multiply with.
	 * @return MatrixClass& this matrix
	 */
	MatrixClass& operator*=(double scalar);

	/**
	 * @brief Division operator (dividing the matrix by the scalar & the result in this matrix).
	 *
	 * @param[in] scalar The scalar to divide with.
	 * @return MatrixClass& this matrix
	 */
	MatrixClass& operator/=(double scalar);

	/**
	 * @brief Destructor for destroying the matrix.
	 */
	~MatrixClass();

//DELETING MOVE METHODS (We would use only cpt methods)
	/**
	 * @brief Constructor, a new Matrix Class object from matrix.
	 * (move Constructor)
	 * 
	 * @param[in] source The matrix to copy.
	 */
	MatrixClass(MatrixClass&& source) = delete;

	/**
	 * @brief assignment opperator (move assignment).
	 *
	 * @param[in] source The assigned MatrixClass.
	 */
	MatrixClass& operator=(MatrixClass&& source) = delete;

//another operators. warning! they return new MatrixClass

	/**
	 * @brief Addition opperator (adds the matrixes & return new matrix).
	 *
	 * @param[in] other The right hand side of the addition operation.
	 * @return MatrixClass& the new result matrix
	 */
	MatrixClass& operator+(const MatrixClass& other) const;

	/**
	 * @brief Minus opperator (reducing the left side by the right side 
	 * & returning a new result matrix)).
	 *
	 * @param[in] other The right hand side of the addition operation.
	 * @return MatrixClass& the new result matrix
	 */
	MatrixClass& operator-(const MatrixClass& other) const;

	/**
	 * @brief Multiplication opperator (multipling the matrixes & return new matrix).
	 *
	 * @param[in] other The right hand side of the multiplication operation.
	 * @return MatrixClass& the new result matrix
	 */
	MatrixClass& operator*(const MatrixClass& other) const;

	/**
	 * @brief Multiplication operator (multipling the matrixe & the scalar
	 *  & return new matrix).
	 *
	 * @param[in] scalar The scalar to multiply with.
	 * @return MatrixClass& the new result matrix
	 */
	MatrixClass& operator*(double scalar) const;

	/**
	 * @brief Division operator (dividing the matrix by the scalar
	 *  & return new matrix).
	 *
	 * @param[in] scalar The scalar to divide with.
	 * @return MatrixClass& the new result matrix
	 */
	MatrixClass& operator/(double scalar) const;

	/**
	 * @brief make a string that represent the matrix.
	 * 
	 * @return string that represent the matrix.
	 */
	string toString() const;

//friends functins

	/**
	 * @brief used for printing the matrix (make it a stream)
	 * 
	 * @param stream to add the matrix to.
	 * @param matrix the matrix to add.
	 * @return std::ostream& the stream with the matrix.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const MatrixClass& matrix);

	/**
	 * @brief Multiplication operator (multipling the matrixe & the scalar
	 *  & return new matrix).
	 *
	 * @param[in] scalar The scalar to multiply with.
	 * @return MatrixClass& the new result matrix
	 */
	friend MatrixClass& operator*(double scalar, const MatrixClass& matrix);
};

}