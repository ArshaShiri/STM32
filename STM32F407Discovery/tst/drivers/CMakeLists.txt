add_executable(driversTest main.cpp gpioRegistersTest.cpp rccRegistersTest.cpp)

target_link_libraries(driversTest PRIVATE GTest::GTest)

target_include_directories(driversTest PUBLIC "${PROJECT_SOURCE_DIR}/src")
