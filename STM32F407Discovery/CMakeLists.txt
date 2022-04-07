cmake_minimum_required(VERSION 3.2)
project(STM32F407 CXX)

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_TARGET "Build target" OFF)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

#Setting up flags for the linker and compiler.
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} ${TARGET_FLAGS}"
    CACHE STRING "" FORCE)

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} ${TARGET_FLAGS}"
    CACHE STRING "" FORCE)

# Adding the src:
if(BUILD_TARGET)
  set(CMAKE_EXECUTABLE_SUFFIX .elf)
endif()

add_subdirectory(src)

# Adding the tests.
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tst)
endif()


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
