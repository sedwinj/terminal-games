cmake_minimum_required(VERSION 3.22)

project (terminal-games VERSION 0)

add_subdirectory(Card)

add_executable(terminal-games
    MainComponent.cpp
    Runner.cpp
)

target_link_libraries(terminal-games PUBLIC Card)

target_include_directories(terminal-games
    PUBLIC "${PROJECT_BINARY_DIR}"
)