add_executable(utilsTest registerAccessTest.cpp)

target_link_libraries(utilsTest
    PRIVATE
    GTest::GTest
)
