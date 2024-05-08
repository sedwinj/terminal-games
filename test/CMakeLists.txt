
add_subdirectory(Card)

add_executable(tests main.cpp Util.test.cpp)
target_link_libraries(tests PRIVATE src Card_Test compile_flags)
