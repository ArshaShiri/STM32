find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_subdirectory(registers)
add_subdirectory(utils)
