#include "lib/catch.hpp"

#include "src/Card.hpp"
#include "src/Util.hpp"

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

  Util::deleteAll({card1, card2, card3, card4, card5});
}

TEST_CASE("Shuffled deck", "[Card::buildShuffledDeck]")
{
  std::mt19937 rng(std::random_device{}());

  std::vector<Card *> ordered = Card::buildDeck();
  std::vector<Card *> shuffle1 = Card::buildShuffledDeck(rng());
  std::vector<Card *> shuffle2 = Card::buildShuffledDeck(rng());

  CHECK(ordered != shuffle1);
  CHECK(shuffle1 != shuffle2);

  Util::deleteAll(ordered);
  Util::deleteAll(shuffle1);
  Util::deleteAll(shuffle2);
}

TEST_CASE("Equality", "[Card::operator==]")
{
  Card *card1 = new Card(12, Card::Suit::HEARTS);
  Card *card2 = new Card(12, Card::Suit::HEARTS);
  Card *card3 = new Card(1, Card::Suit::SPADES);

  CHECK(*card1 == *card2);
  CHECK(*card1 != *card3);

  Util::deleteAll({card1, card2, card3});
}

TEST_CASE("Parsing", "[Card::parse]")
{
  Card *truth = new Card(12, Card::Suit::HEARTS);

  Card *card1 = Card::parse("QH");
  Card *card2 = Card::parse("12H");
  Card *card3 = Card::parse("Q H");
  Card *card4 = Card::parse("12 H");
  Card *card5 = Card::parse("Queen of Hearts");
  Card *card6 = Card::parse("12 of Hearts");
  Card *card7 = Card::parse("Twelve of Hearts");

  CHECK(*truth == *card1);
  CHECK(*truth == *card2);
  CHECK(*truth == *card3);
  CHECK(*truth == *card4);
  CHECK(*truth == *card5);
  CHECK(*truth == *card6);
  CHECK(*truth == *card7);

  Util::deleteAll({truth, card1, card2, card3, card4, card5, card6, card7});
}

TEST_CASE("Parsing symbol notation", "[Card::parse]")
{
  CHECK_NOTHROW(delete Card::parse("12H"));
  CHECK_NOTHROW(delete Card::parse("AH"));
  CHECK_NOTHROW(delete Card::parse("XC"));
  CHECK_NOTHROW(delete Card::parse("jd"));
  CHECK_NOTHROW(delete Card::parse("qs"));
  CHECK_NOTHROW(delete Card::parse("ks"));

  CHECK_THROWS_AS(Card::parse("14h"), std::invalid_argument);
  CHECK_THROWS_AS(Card::parse("hq"), std::invalid_argument);
}

TEST_CASE("toSymbol", "[Card::toSymbol]")
{
  // TODO: implement

  // Generate
  std::vector<std::string> values{"A", "X", "J", "Q", "K"};
  for (int i = 2; i < 10; i++)
    values.push_back(std::to_string(i));

  for (auto value : values)
  {
    for (std::string suit : std::vector<std::string>{"C", "D", "H", "S"})
    {
      Card *card = Card::parse(value + suit);
      std::string symbol = card->toSymbol();
      CHECK(value + suit == symbol);
      delete card;
    }
  }
}