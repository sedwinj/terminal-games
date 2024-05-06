#include "lib/catch.hpp"

#include "src/Card/Suit.hpp"

TEST_CASE("Suits are correctly returned", "[Suit::getSuits]")
{
  auto suits = Suit::getSuits();
  REQUIRE(suits.size() == 4);
}