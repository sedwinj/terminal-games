cmake_minimum_required(VERSION 3.22)

project(terminal-games VERSION 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(src)

option(BUILD_TESTS "Will build Catch test suite when set to ON." ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()