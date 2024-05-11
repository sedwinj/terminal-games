add_executable(tests
    main.cpp
    Card.test.cpp
    Util.test.cpp
)
target_link_libraries(tests PRIVATE src compile_flags)
