#include "ErrorCodeException.hpp"

//Implementing methods
	matrix::ErrorCodeException::ErrorCodeException(const ErrorCode er) : m_errorCode(er){}

  bool matrix::ErrorCodeException::isSuccess() const{
    return error_isSuccess(m_errorCode); 
  }

  const char* matrix::ErrorCodeException::what() const noexcept{
		return error_getErrorMessage(m_errorCode); 
	}

  void matrix::ErrorCodeException::throwErrorIfNeeded(const ErrorCode er){
    //checking success
    matrix::ErrorCodeException exeption = ErrorCodeException(er);
    if(!exeption.isSuccess()) {
      throw exeption;
    }
  }
