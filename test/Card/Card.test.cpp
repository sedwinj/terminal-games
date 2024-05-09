#include "lib/catch.hpp"

#include "src/Card/Card.hpp"

TEST_CASE("Constructors", "[Card::Card]")
{
  Card *card1 = new Card(12, Card::Suit::HEARTS);
  Card *card2 = new Card(12, "hearts");
  Card *card3 = new Card("twelve", Card::Suit::HEARTS);
  Card *card4 = new Card("twelve", "hearts");
  Card *card5 = new Card(*card4);

  CHECK((card1->getValue() == 12 && card1->getSuit() == Card::Suit::HEARTS));
  CHECK((card2->getValue() == 12 && card2->getSuit() == Card::Suit::HEARTS));
  CHECK((card3->getValue() == 12 && card3->getSuit() == Card::Suit::HEARTS));
  CHECK((card4->getValue() == 12 && card4->getSuit() == Card::Suit::HEARTS));
  CHECK((card5->getValue() == 12 && card5->getSuit() == Card::Suit::HEARTS));
}

TEST_CASE("Equality", "[Card]::==")
{
  Card *card1 = new Card(12, Card::Suit::HEARTS);
  Card *card2 = new Card(12, Card::Suit::HEARTS);
  Card *card3 = new Card(1, Card::Suit::SPADES);

  CHECK(*card1 == *card2);
  CHECK(*card1 != *card3);
}

TEST_CASE("Parsing", "[Card::parse]")
{
  Card *truth = new Card(12, Card::Suit::HEARTS);

  CHECK(*truth == *Card::parse("QH"));
  CHECK(*truth == *Card::parse("12H"));
  CHECK(*truth == *Card::parse("Q H"));
  CHECK(*truth == *Card::parse("12 H"));
  CHECK(*truth == *Card::parse("Queen of Hearts"));
  CHECK(*truth == *Card::parse("12 of Hearts"));
  CHECK(*truth == *Card::parse("Twelve of Hearts"));
}

TEST_CASE("Parsing symbol notation", "[Card::parse]")
{
  Card::parse("12H");
  Card::parse("AH");
  Card::parse("XC");
  Card::parse("jd");
  Card::parse("qs");
  Card::parse("ks");
  Card::parse("14k");
}

TEST_CASE("toSymbol", "[Card::toSymbol]")
{
  std::vector<std::string> symbols;
  for (int value = 1; value <= 13; value++)
  {
    std::string valueStr = std::to_string(value);
    symbols.push_back(valueStr + "C");
  }
}