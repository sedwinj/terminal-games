add_library(Card Suit.cpp)

target_include_directories (Card
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)