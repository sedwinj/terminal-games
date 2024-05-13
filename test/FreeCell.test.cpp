#include "lib/catch.hpp"

#include "src/FreeCell.hpp"

TEST_CASE("board construction and representation", "FreeCell::Board")
{
  FreeCell::Board board = FreeCell::Board(Card::buildDeck());

  std::string expected = "[] [] [] []       [] [] [] []\n"
                         "   AC 2C 3C 4C 5C 6C 7C 8C   \n"
                         "   9C XC JC QC KC AD 2D 3D   \n"
                         "   4D 5D 6D 7D 8D 9D XD JD   \n"
                         "   QD KD AH 2H 3H 4H 5H 6H   \n"
                         "   7H 8H 9H XH JH QH KH AS   \n"
                         "   2S 3S 4S 5S 6S 7S 8S 9S   \n"
                         "   XS JS QS KS               \n";
  auto actual = board.toString();
  CHECK(actual == expected);
}