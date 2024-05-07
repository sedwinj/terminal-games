add_subdirectory(Card)

add_library(src MainComponent.cpp)
target_link_libraries(src PUBLIC Card)

add_executable(terminal-games Runner.cpp)
target_link_libraries(terminal-games PUBLIC src)
