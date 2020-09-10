#pragma once

#include "crc32.hpp"
#include "file_reading.hpp"

#include <string.h>
#include <string>
#include <algorithm>

/**
 * @brief Performs the crc32 algorithem on file.
 * 
 * @param filePath - the input bit array is in the file.
 * @return uint32_t the crc32 on the file.
 */
std::uint32_t crc32(const std::string& filePath);

/**
 * @brief Performs the crc32 algorithem on string.
 * 
 * @param s - the input in string.
 * @return uint32_t the crc32 on the string.
 */
std::uint32_t crc32FromString(const std::string& file);
