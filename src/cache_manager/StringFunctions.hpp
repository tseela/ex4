#include <string>

/**
 * @brief this namespace is a group of functions to
 * help in the operation and his sub classes. 
 */
namespace OperatorsHelpingFuncs {

/**
 * @brief Copy a string from char* to std::string.
 * 
 * @param charArray - the string in char*.
 * @return string 
 */
std::string copyToString(const char *charArray);

/**
 * @brief Checks if a file is typed "type".
 * 
 * @param fileName - the name if the file.
 * @param type - the type we are checking.
 * @return true or false
 */
bool typed(const std::string& fileName, const std::string& type);
}