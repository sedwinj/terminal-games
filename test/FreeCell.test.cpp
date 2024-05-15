#include "lib/catch.hpp"

#include "src/FreeCell.hpp"

TEST_CASE("construction and representation", "FreeCell::Board")
{
  FreeCell::Board board1 = FreeCell::Board(Card::buildDeck());
  std::string expected1 = "[] [] [] []       [] [] [] []\n"
                          "   AS 2S 3S 4S 5S 6S 7S 8S   \n"
                          "   9S XS JS QS KS AH 2H 3H   \n"
                          "   4H 5H 6H 7H 8H 9H XH JH   \n"
                          "   QH KH AD 2D 3D 4D 5D 6D   \n"
                          "   7D 8D 9D XD JD QD KD AC   \n"
                          "   2C 3C 4C 5C 6C 7C 8C 9C   \n"
                          "   XC JC QC KC               \n";
  CHECK(board1.toString() == expected1);

  FreeCell::Board board2 = FreeCell::Board(std::vector<Card *>());
  std::string expected2 = "[] [] [] []       [] [] [] []\n"
                          "   [] [] [] [] [] [] [] []   \n";
  CHECK(board2.toString() == expected2);
}

TEST_CASE("copy construction and equivalence", "FreeCell::Board")
{
  FreeCell::Board board1 = FreeCell::Board(Card::buildDeck());
  FreeCell::Board board2 = FreeCell::Board(board1);
  CHECK(board1 == board2);
}