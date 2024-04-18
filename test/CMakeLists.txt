Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

option(MAKE_TESTS ON)
if(MAKE_TESTS)
    add_executable(terminal-games-test
        test.cpp
    )
    target_link_libraries(terminal-games-test PUBLIC test)
    target_include_directories(terminal-games-test PUBLIC
        "${PROJECT_BINARY_DIR}"
        # "${PROJECT_SOURCE_DIR}/Card"
    )
endif()

add_executable(terminal-games-test test.cpp)
target_link_libraries(terminal-games-test PRIVATE Catch2::Catch2WithMain)