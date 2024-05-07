#include <memory>

#include "lib/catch.hpp"

#include "src/Card/Card.hpp"

TEST_CASE("Persistence", "[Card::Card]")
{
  Card *card = new Card(12, Card::Suit::HEARTS);

  REQUIRE(card->getValue() == 12);
  REQUIRE(card->getSuit() == Card::Suit::HEARTS);
}

TEST_CASE("Equality", "[Card]::==")
{
  Card *card1 = new Card(12, Card::Suit::HEARTS);
  Card *card2 = new Card(12, Card::Suit::HEARTS);
  Card *card3 = new Card(1, Card::Suit::SPADES);

  REQUIRE(*card1 == *card2);
  REQUIRE(*card1 != *card3);
}

TEST_CASE("Parsing", "[Card::parse]")
{
  Card *truth = new Card(12, Card::Suit::HEARTS);

  REQUIRE(*truth == *Card::parse("QH"));
  REQUIRE(*truth == *Card::parse("12H"));
  REQUIRE(*truth == *Card::parse("Q H"));
  REQUIRE(*truth == *Card::parse("12 H"));
  REQUIRE(*truth == *Card::parse("Queen of Hearts"));
  REQUIRE(*truth == *Card::parse("12 of Hearts"));
  REQUIRE(*truth == *Card::parse("Twelve of Hearts"));
}