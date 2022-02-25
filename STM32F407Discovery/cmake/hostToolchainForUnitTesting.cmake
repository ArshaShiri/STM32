set(CMAKE_SYSTEM_NAME "${CMAKE_HOST_SYSTEM_NAME}")

set (CMAKE_CXX_COMPILER "g++")

set(extraOpts "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_INIT "${extraOpts} -pedantic")
