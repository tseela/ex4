
cmake_minimum_required(VERSION 3.0.0)
project(ex4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

#add_compile_options(-Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor -Wshadow)

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add the libmatrix file to the include path - so that
#   we can include it as without explicitly specifying 
#   the files directory.
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/files)

# Link directories - tells the linker to look for .so files
#   in these directories. We want libmatrix.so which is under 
#   the matrix directory. Note that a full path is required.
link_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/files)


add_executable(tester.out main.cpp files/file_reading.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)