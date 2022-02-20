# Generic is used for bare metal embedded devices.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set (CROSS_COMPILER "arm-none-eabi-")
set (CMAKE_CXX_COMPILER "${CROSS_COMPILER}gcc")

set(extraOpts "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_INIT "${extraOpts} -pedantic")
