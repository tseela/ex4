#include "ErrorCodeException.hpp"

//Implementing methods
	matrix::ErrorCodeException::ErrorCodeException(const ErrorCode er) : _errorCode(er){}

  bool matrix::ErrorCodeException::isSuccess() const{
    return error_isSuccess(_errorCode); 
  }

  void matrix::ErrorCodeException::printErrorMessage() const{
    //prints the error messege
		cerr << error_getErrorMessage(_errorCode) << endl; 
	}

  void matrix::ErrorCodeException::throwErrorIfNeeded(ErrorCode er){
    //checking success
    ErrorCodeException exeption = ErrorCodeException(er);
    if (!exeption.isSuccess()) {
      throw exeption;
    }
  }
