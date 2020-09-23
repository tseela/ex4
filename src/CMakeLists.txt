
cmake_minimum_required(VERSION 3.0.0)
project(ex4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor -Wshadow)

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/files ${CMAKE_SOURCE_DIR}/solver
${CMAKE_SOURCE_DIR}/matrix ${CMAKE_SOURCE_DIR}/graph ${CMAKE_SOURCE_DIR}/time ${CMAKE_SOURCE_DIR}/solver/cache_manager
${CMAKE_SOURCE_DIR}/solver/solutions/graph_algorithms/helpers ${CMAKE_SOURCE_DIR}/solver/problems
${CMAKE_SOURCE_DIR}/solver/solutions ${CMAKE_SOURCE_DIR}/solver/solutions/graph_algorithms
${CMAKE_SOURCE_DIR}/solver/cache_manager/hash ${CMAKE_SOURCE_DIR}/server ${PARENT_DIR}/lib)

link_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/files ${CMAKE_SOURCE_DIR}/solver
${CMAKE_SOURCE_DIR}/matrix ${CMAKE_SOURCE_DIR}/graph ${CMAKE_SOURCE_DIR}/time ${CMAKE_SOURCE_DIR}/solver/solutions/helpers
${CMAKE_SOURCE_DIR}/solver/cache_manager ${CMAKE_SOURCE_DIR}/solver/problems ${CMAKE_SOURCE_DIR}/solver/solutions
${CMAKE_SOURCE_DIR}/solver/cache_manager/hash ${CMAKE_SOURCE_DIR}/server ${PARENT_DIR}/lib)


add_executable(ex4.out main.cpp
files/file_reading.cpp graph/Graph.cpp matrix/ErrorCodeException.cpp matrix/MatrixClass.cpp time/CurrentTime.cpp
solver/Solver.cpp solver/problems/Problem.cpp solver/problems/MatrixGraphProblem.cpp
solver/solutions/Solution.cpp solver/solutions/graph_algorithms/MatrixGraphSolution.cpp solver/solutions/graph_algorithms/DFS.cpp
solver/solutions/graph_algorithms/BFS.cpp solver/solutions/graph_algorithms/A*.cpp solver/solutions/graph_algorithms/helpers/BestPath.cpp
solver/cache_manager/CacheManager.cpp solver/cache_manager/StringFunctions.cpp solver/cache_manager/Operation.cpp
solver/cache_manager/hash/crc32.cpp solver/cache_manager/hash/crc32FileReader.cpp)
target_link_libraries(ex4.out matrix)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)