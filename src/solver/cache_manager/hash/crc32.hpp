#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * @brief the fuction to calculat crc32.
 * 
 * @param buf the buufer.
 * @param size of the buffer.
 * @return uint32_t the crc32 from the buffer.
 */
uint32_t crc32(const void *buf, size_t size);