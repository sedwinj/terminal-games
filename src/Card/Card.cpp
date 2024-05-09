#include "Card.hpp"

const std::map<std::string, Card::Suit> Card::suitFromString = buildSuitFromString();
const std::map<Card::Suit, std::string> Card::suitToString = buildSuitToString();
const std::map<std::string, int> Card::valueFromString = buildValueFromString();
const std::map<int, std::string> Card::valueToString = buildValueToString();

Card::Card(int value, Suit suit) : value(value), suit(suit) {}

Card::Card(int value, std::string suit) : value(value),
                                          suit(suitFromString.at(suit)) {}

Card::Card(std::string value, Suit suit) : value(valueFromString.at(value)),
                                           suit(suit) {}

Card::Card(std::string value, std::string suit) : value(valueFromString.at(value)),
                                                  suit(suitFromString.at(suit)) {}

Card::Card(const Card &other) : value(other.value), suit(other.suit) {}

std::map<std::string, Card::Suit> Card::buildSuitFromString()
{
  auto map = std::map<std::string, Card::Suit>();

  map["c"] = Card::Suit::CLUBS;
  map["club"] = Card::Suit::CLUBS;
  map["clubs"] = Card::Suit::CLUBS;
  map["d"] = Card::Suit::DIAMONDS;
  map["diamond"] = Card::Suit::DIAMONDS;
  map["diamonds"] = Card::Suit::DIAMONDS;
  map["h"] = Card::Suit::HEARTS;
  map["heart"] = Card::Suit::HEARTS;
  map["hearts"] = Card::Suit::HEARTS;
  map["s"] = Card::Suit::SPADES;
  map["spade"] = Card::Suit::SPADES;
  map["spades"] = Card::Suit::SPADES;

  return map;
}

std::map<Card::Suit, std::string> Card::buildSuitToString()
{
  std::map<Suit, std::string> map;
  map[Suit::CLUBS] = "Clubs";
  map[Suit::DIAMONDS] = "Diamonds";
  map[Suit::HEARTS] = "Hearts";
  map[Suit::SPADES] = "Spades";

  return map;
}

std::map<std::string, int> Card::buildValueFromString()
{
  auto map = std::map<std::string, int>();

  for (int value = 1; value <= 13; value++)
  {
    map[std::to_string(value)] = value;
  }

  map["one"] = 1;
  map["two"] = 2;
  map["three"] = 3;
  map["four"] = 4;
  map["five"] = 5;
  map["six"] = 6;
  map["seven"] = 7;
  map["eight"] = 8;
  map["nine"] = 9;
  map["ten"] = 10;
  map["eleven"] = 11;
  map["twelve"] = 12;
  map["thirteen"] = 13;

  map["a"] = 1;
  map["ace"] = 1;
  map["x"] = 10;
  map["j"] = 11;
  map["jack"] = 11;
  map["q"] = 12;
  map["queen"] = 12;
  map["k"] = 13;
  map["king"] = 13;

  return map;
}

std::map<int, std::string> Card::buildValueToString()
{
  std::map<int, std::string> map;
  map[1] = "Ace";
  map[2] = "Two";
  map[3] = "Three";
  map[4] = "Four";
  map[5] = "Five";
  map[6] = "Six";
  map[7] = "Seven";
  map[8] = "Eight";
  map[9] = "Nine";
  map[10] = "Ten";
  map[11] = "Jack";
  map[12] = "Queen";
  map[13] = "King";

  return map;
}

Card::Suit Card::getSuit() const
{
  return suit;
}

int Card::getValue() const
{
  return value;
}

std::vector<Card *> Card::newDeck()
{
  // TODO: implement
}

bool Card::operator==(const Card &other) const
{
  return value == other.value && suit == other.suit;
}

bool Card::operator!=(const Card &other) const
{
  return !(*this == other);
}

Card *Card::parse(std::string str)
{
  str = Util::stringLower(str);

  std::string value = "";
  std::string suit = "";
  if (2 <= str.size() <= 3 && str.find(" ") == std::string::npos)
  {
    value = str.substr(0, str.size() - 1);
    suit = str.substr(str.size() - 1);
  }
  else
  {
    // Find a valid value-suit split
    auto split = Util::stringSplit(str, " of ");
    if (split.size() == 1)
    {
      split = Util::stringSplit(str, " ");
    }
    value = split[0];
    suit = split[1];
  }

  return new Card(valueFromString.at(value), suitFromString.at(suit));
}

std::string Card::toString()
{
  return valueToString.at(value) + " of " + suitToString.at(suit);
}

std::string Card::toSymbol()
{
  // TODO: implement
}