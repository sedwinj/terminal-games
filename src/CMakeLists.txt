add_library(src 
    MainComponent.cpp
    Card.cpp
    Freecell.cpp
)
target_link_libraries(src PUBLIC compile_flags)

add_executable(terminal-games Runner.cpp)
target_link_libraries(terminal-games PUBLIC src)
