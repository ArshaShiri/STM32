cmake_minimum_required(VERSION 3.2)

project(test CXX)
set(CMAKE_CXX_STANDARD 20)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests testing.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
