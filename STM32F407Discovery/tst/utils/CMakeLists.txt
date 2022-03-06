add_executable(utilsTest registerAccessTest.cpp)

target_link_libraries(utilsTest PRIVATE GTest::GTest)

target_include_directories(utilsTest PUBLIC "${PROJECT_SOURCE_DIR}/src")
