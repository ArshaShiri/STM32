add_executable(driversTest gpioRegistersTest.cpp)

target_link_libraries(driversTest PRIVATE GTest::GTest)

target_include_directories(driversTest PUBLIC "${PROJECT_SOURCE_DIR}/src")
