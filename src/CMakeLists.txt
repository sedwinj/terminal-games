add_library(src 
    MainComponent.cpp
    Card.cpp
    FreeCell.cpp
)
target_link_libraries(src PUBLIC compile_flags)

add_executable(terminal-games main.cpp)
target_link_libraries(terminal-games PUBLIC src)
