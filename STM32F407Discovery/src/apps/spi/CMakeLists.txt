set(NAME_OF_APP spi)

add_executable(${NAME_OF_APP} spi.cpp ${CMAKE_SOURCE_DIR}/src/targetSpecific/startup.cpp)

target_include_directories(${NAME_OF_APP} PUBLIC "${PROJECT_SOURCE_DIR}/src")
