cmake_minimum_required(VERSION 3.2)
project(STM32F407Discovery CXX)
#enable_testing()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ${target_arch})

# # src/tests/CMakeLists.txt
# include(ExternalProject)

# ExternalProject_Add(
#     googletest
#     GIT_REPOSITORY https://github.com/google/googletest
#     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
# )
# include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
# link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# file(GLOB TESTS "*.cpp")
# add_executable(tests ${TESTS})
# target_link_libraries(tests soccl gtest gmock gtest_main pthread)
