cmake_minimum_required(VERSION 3.22)

project(terminal-games VERSION 0)

add_library(compile_flags INTERFACE)
target_compile_features(compile_flags INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClangAppleClang,Clang,GNU,LCC>")

target_compile_options(compile_flags INTERFACE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(src)

option(BUILD_TESTS "Will build Catch test suite when set to ON." ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()