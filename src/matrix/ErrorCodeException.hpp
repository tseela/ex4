#pragma once

#include "ErrorCode.h"

#include <iostream>

using std::endl;
using std::cerr;

namespace matrix {

class ErrorCodeException{
//Fields
const ErrorCode _errorCode;

//methods
public:

	/**
 	* @brief Construct a new ErrorCodeException object.
 	* 
 	* @param code The ErrorCode.
 	*/
	explicit ErrorCodeException(const ErrorCode er);

	/**
	 * @brief Checks if error code indicates a success or not.
	 *
	 * @return whether the error code indicates a success or not.
	 */
	bool isSuccess() const;

	/**
	 * @brief Checks prints error code's error message.
	 */
	void printErrorMessage() const;

	/**
	 * @brief Destroy the ErrorCodeException object.
	 * 
	 */
	~ErrorCodeException() = default;

	/**
     * @brief gets ErrorCode & if it's not success throws 
	 * ErrorCodeException with the same ErrorCode.
     * 
     * @param er the ErrorCode.
     */
    static void throwErrorIfNeeded(ErrorCode er);
};

}