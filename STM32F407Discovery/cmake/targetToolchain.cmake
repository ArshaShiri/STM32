message("Setting up toolchain")

# Generic is used for bare metal embedded devices.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(GCC_TOOLCHAIN_PREFIX "arm-none-eabi-")

execute_process(
  COMMAND which ${GCC_TOOLCHAIN_PREFIX}g++
  OUTPUT_VARIABLE UTILS_PATH
  OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_SYSROOT ${UTILS_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_AR ${GCC_TOOLCHAIN_PREFIX}ar)
set(CMAKE_ASM_COMPILER ${GCC_TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CC_COMPILER ${GCC_TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER "${GCC_TOOLCHAIN_PREFIX}g++")

set(OBJDUMP ${GCC_TOOLCHAIN_PREFIX}objdump)
set(OBJCOPY ${GCC_TOOLCHAIN_PREFIX}objcopy)
set(READELF ${GCC_TOOLCHAIN_PREFIX}readelf)

set(CMAKE_CXX_FLAGS_INIT
    "-Wall -Wextra -pedantic -Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough"
)

set(LINKER_DEFINITION_FILE, "../linkerScript.ld")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-T ${LINKER_DEFINITION_FILE} -Wl,--gc-sections -Wl,-Map=final.map")
