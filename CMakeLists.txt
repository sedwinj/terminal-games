cmake_minimum_required(VERSION 3.22)

project(terminal-games VERSION 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

add_subdirectory(src)
add_subdirectory(test)