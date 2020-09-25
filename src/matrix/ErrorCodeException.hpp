#pragma once

#include "ErrorCode.h"

#include <iostream>
#include <exception>

using std::endl;
using std::cerr;

namespace matrix {

class ErrorCodeException : public std::exception{
//Fields
ErrorCode m_errorCode;

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
	virtual const char* what() const noexcept override;

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
    static void throwErrorIfNeeded(const ErrorCode er);
};

}