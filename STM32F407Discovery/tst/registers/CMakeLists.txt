add_executable(registersTest extiRegistersTest.cpp
                             gpioRegistersTest.cpp
                             i2cRegistersTest.cpp
                             interruptRegistersTest.cpp
                             main.cpp
                             rccRegistersTest.cpp
                             spiRegistersTest.cpp
                             syscfgRegistersTest.cpp
)

target_link_libraries(registersTest PRIVATE GTest::GTest)

target_include_directories(registersTest PUBLIC "${PROJECT_SOURCE_DIR}/src")
