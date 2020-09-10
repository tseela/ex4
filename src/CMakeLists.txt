
cmake_minimum_required(VERSION 3.0.0)
project(ex2 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor -Wshadow)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add the libmatrix file to the include path - so that
#   we can include it as without explicitly specifying 
#   the files directory.
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/files ${CMAKE_SOURCE_DIR}/hash
${CMAKE_SOURCE_DIR}/matrix ${CMAKE_SOURCE_DIR}/cache_manager
${CMAKE_SOURCE_DIR}/cache_manager/time ${CMAKE_SOURCE_DIR}/../lib)
# Link directories - tells the linker to look for .so files
#   in these directories. We want libmatrix.so which is under 
#   the matrix directory. Note that a full path is required.
link_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/files ${CMAKE_SOURCE_DIR}/hash
${CMAKE_SOURCE_DIR}/matrix ${CMAKE_SOURCE_DIR}/cache_manager
${CMAKE_SOURCE_DIR}/cache_manager/time ${CMAKE_SOURCE_DIR}/../lib)


add_executable(ex3.out main.cpp
                cache_manager/CacheManager.cpp cache_manager/StringFunctions.cpp
                cache_manager/operations/Operation.cpp cache_manager/time/CurrentTime.cpp files/file_reading.cpp
                hash/crc32.cpp hash/crc32FileReader.cpp matrix/ErrorCodeException.cpp matrix/MatrixClass.cpp)
target_link_libraries(ex3.out matrix)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)