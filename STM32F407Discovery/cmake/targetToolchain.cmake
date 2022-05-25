message("Setting up toolchain")

# Generic is used for bare metal embedded devices.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

message("CMAKE_EXECUTABLE_SUFFIX is ${CMAKE_EXECUTABLE_SUFFIX}")

set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS NO)

set(TARGET_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=soft")

set(GCC_TOOLCHAIN_PREFIX "arm-none-eabi-")

execute_process(
  COMMAND which ${GCC_TOOLCHAIN_PREFIX}g++
  OUTPUT_VARIABLE UTILS_PATH
  OUTPUT_STRIP_TRAILING_WHITESPACE)

message("Utils path: ${UTILS_PATH}")

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

set(COMMON_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=soft")

# Add -specs=nosys.specs to avoid missing -exit reference.
set(CMAKE_CXX_FLAGS_INIT
    "${CMAKE_CXX_FLAGS}
    ${COMMON_FLAGS}
    -specs=nosys.specs
    -Wall
    -Wextra
    -pedantic
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
    -Wimplicit-fallthrough
    -fno-exceptions"
)

# Remove new line chars from the flags.
string(REPLACE "\n" " " CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")

set(CMAKE_EXE_LINKER_FLAGS_INIT
    "${COMMON_FLAGS} -T ${CMAKE_SOURCE_DIR}/src/targetSpecific/linkerScript.ld -Wl,-Map=memroy.map")

# get rid of -rdynamic
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
