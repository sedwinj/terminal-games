cmake_minimum_required(VERSION 3.22)

project (terminal-games VERSION 0)

add_executable(terminal-games
    MainComponent.cpp
    Runner.cpp
)

target_include_directories(terminal-games PRIVATE
    "${PROJECT_BINARY_DIR}"
)