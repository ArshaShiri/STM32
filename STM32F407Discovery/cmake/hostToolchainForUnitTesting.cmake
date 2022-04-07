set(CMAKE_SYSTEM_NAME "${CMAKE_HOST_SYSTEM_NAME}")

set (CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_CXX_FLAGS_INIT
    "-Wall
    -Wextra
    -pedantic
    -Werror
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
    -Wimplicit-fallthrough"
)

# Remove new line chars from the flags.
string(REPLACE "\n" " " CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
