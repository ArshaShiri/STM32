set(NAMEOFAPP led)

add_executable(${NAMEOFAPP} led.cpp ${CMAKE_SOURCE_DIR}/src/targetSpecific/startup.cpp)

target_include_directories(${NAMEOFAPP} PUBLIC "${PROJECT_SOURCE_DIR}/src")
