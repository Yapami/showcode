cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME Bit_count)
project(${PROJECT_NAME})

find_package(GTest REQUIRED)

include(GoogleTest)

enable_testing()

set(SOURCES Bit_count.cpp)

set(APP_SOURCES ${SOURCES} main.cpp)
set(TEST_SOURCES ${SOURCES} Bit_count_GTest.cpp)

add_executable(${PROJECT_NAME} ${APP_SOURCES})
add_executable(test-${PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(test-${PROJECT_NAME} gtest gtest_main gmock pthread)

gtest_discover_tests(test-${PROJECT_NAME})
