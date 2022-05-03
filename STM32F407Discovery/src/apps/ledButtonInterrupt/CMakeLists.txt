set(NAME_OF_APP ledButtonInterrupt)

add_executable(${NAME_OF_APP} ledButtonInterrupt.cpp ${CMAKE_SOURCE_DIR}/src/targetSpecific/startup.cpp)

target_include_directories(${NAME_OF_APP} PUBLIC "${PROJECT_SOURCE_DIR}/src")
