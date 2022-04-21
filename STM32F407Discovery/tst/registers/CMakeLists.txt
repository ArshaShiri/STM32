add_executable(registersTest main.cpp gpioRegistersTest.cpp rccRegistersTest.cpp extiRegistersTest.cpp)

target_link_libraries(registersTest PRIVATE GTest::GTest)

target_include_directories(registersTest PUBLIC "${PROJECT_SOURCE_DIR}/src")
