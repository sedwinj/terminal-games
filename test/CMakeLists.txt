
add_subdirectory(Card)

add_executable(tests main.cpp Util.test.cpp)
target_link_libraries(tests PRIVATE
    src
    Card_Test
)

option(POST_TEST "Will test after building Catch suite when set to ON." ON)
if(POST_TEST)
    add_custom_command(TARGET tests
        COMMAND tests
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/../bin
        COMMENT "Running post-build tests..."
    )
endif()
