add_subdirectory(Card)

add_library(terminal_games MainComponent.cpp)
target_link_libraries(terminal_games PUBLIC Card)

add_executable(terminal-games Runner.cpp)
target_link_libraries(terminal-games PUBLIC terminal_games)
