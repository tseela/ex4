#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif 

typedef enum {
    // DON'T CHANGE THIS VALUE!
    ERROR_SUCCESS = 0,
    ERROR_ALLOCATING_MEMORY = 1,
    ERROR_PARAMETER_IS_NULL = 2,
    ERROR_INDEX_OUT_OF_BOUNDARY = 3,
    ERROR_MATRIXES_IN_DIFFERENT_SIZE = 4,
    ERROR_MATRIXES_CANT_BE_MULTIPLIED = 5,
    ERROR_MATRIX_IS_NOT_INTALIZED_WELL = 6, //one or more value in the matrix is NULL
    ERROR_MATRIX_SIZE_EQUALS_ZERO = 7
} ErrorCode;

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code);

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code);
}
