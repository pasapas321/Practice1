cmake_minimum_required(VERSION 3.12.4)
project(Practice_1)

set(CMAKE_CXX_STANDARD 20)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR} src)
add_subdirectory(src)

add_executable(tests tests_main.cpp tests/tests.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES} SolverLib)

add_executable(practice main.cpp)
target_link_libraries(practice SolverLib)