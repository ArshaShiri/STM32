cmake_minimum_required(VERSION 3.2)

project(POC CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set (CROSS_COMPILE "arm-none-eabi-")
set (CMAKE_CXX_COMPILER "${CROSS_COMPILE}gcc")
set (CMAKE_ASM_COMPILER "${CROSS_COMPILE}as")

###########
# Debug or Release
###########
if (NOT CMAKE_BUILD_TYPE)
  ## set default to Release
  set(CMAKE_BUILD_TYPE Release)  # override with -DCMAKE_BUILD_TYPE=Debug
  message("==> CMAKE_BUILD_TYPE empty. Changing it to Release.")
else()
  message("==> CMAKE_BUILD_TYPE == ${CMAKE_BUILD_TYPE}.")
endif()

###########
# Warnings
###########
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

##############
# C++ Standard
##############
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

###############
# Flags
###############
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -specs=nosys.specs")

# get rid of -rdynamic
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
set (CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(src src/main.cpp src/startup.cpp)

add_executable(${PROJECT_NAME} ${src})

#set(target_with_suffix "${target}${CMAKE_EXECUTABLE_SUFFIX}")
