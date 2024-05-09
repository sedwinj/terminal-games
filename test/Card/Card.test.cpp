#include "lib/catch.hpp"

#include "src/Card/Card.hpp"

TEST_CASE("Constructors", "[Card::Card]")
{
  Card *card1 = new Card(12, Card::Suit::HEARTS);
  Card *card2 = new Card(12, "hearts");
  Card *card3 = new Card("twelve", Card::Suit::HEARTS);
  Card *card4 = new Card("twelve", "hearts");
  Card *card5 = new Card(*card4);

  REQUIRE((card1->getValue() == 12 && card1->getSuit() == Card::Suit::HEARTS));
  REQUIRE((card2->getValue() == 12 && card2->getSuit() == Card::Suit::HEARTS));
  REQUIRE((card3->getValue() == 12 && card3->getSuit() == Card::Suit::HEARTS));
  REQUIRE((card4->getValue() == 12 && card4->getSuit() == Card::Suit::HEARTS));
  REQUIRE((card5->getValue() == 12 && card5->getSuit() == Card::Suit::HEARTS));
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