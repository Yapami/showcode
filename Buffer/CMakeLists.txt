cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME Buffer)
project(${PROJECT_NAME})

find_package(GTest REQUIRED)

include(GoogleTest)

enable_testing()

set(SOURCES Buffer.cpp)

set(TEST_SOURCES ${SOURCES} Buffer_GTest.cpp)

add_executable(test-${PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(test-${PROJECT_NAME} gtest gtest_main gmock pthread)

gtest_discover_tests(test-${PROJECT_NAME})