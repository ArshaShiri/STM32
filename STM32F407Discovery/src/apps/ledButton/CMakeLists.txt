set(NAME_OF_APP ledButton)

add_executable(${NAME_OF_APP} ledButton.cpp ${CMAKE_SOURCE_DIR}/src/targetSpecific/startup.cpp)

target_include_directories(${NAME_OF_APP} PUBLIC "${PROJECT_SOURCE_DIR}/src")
