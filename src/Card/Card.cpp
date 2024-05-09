#include "Card.hpp"

const std::map<std::string, Card::Suit> Card::stringToSuitLookup = {
    {"c", CLUBS},
    {"club", CLUBS},
    {"clubs", CLUBS},
    {"d", DIAMONDS},
    {"diamond", DIAMONDS},
    {"diamonds", DIAMONDS},
    {"h", HEARTS},
    {"heart", HEARTS},
    {"hearts", HEARTS},
    {"s", SPADES},
    {"spade", SPADES},
    {"spades", SPADES},
};

const std::map<std::string, int> Card::stringToValueLookup = buildStringToValueLookup();

const std::map<Card::Suit, std::string> Card::suitToStringLookup = {
    {Suit::CLUBS, "Clubs"},
    {Suit::DIAMONDS, "Diamonds"},
    {Suit::HEARTS, "Hearts"},
    {Suit::SPADES, "Spades"},
};

const std::map<Card::Suit, std::string> Card::suitToSymbolLookup = {
    {Card::Suit::CLUBS, "C"},
    {Card::Suit::DIAMONDS, "D"},
    {Card::Suit::HEARTS, "H"},
    {Card::Suit::SPADES, "S"},
};

const std::map<int, std::string> Card::valueToStringLookup = {
    {1, "Ace"},
    {2, "Two"},
    {3, "Three"},
    {4, "Four"},
    {5, "Five"},
    {6, "Six"},
    {7, "Seven"},
    {8, "Eight"},
    {9, "Nine"},
    {10, "Ten"},
    {11, "Jack"},
    {12, "Queen"},
    {13, "King"},
};

const std::map<int, std::string> Card::valueToSymbolLookup = {
    {1, "A"},
    {10, "X"},
    {11, "J"},
    {12, "Q"},
    {13, "K"},
};

Card::Card(int value, Suit suit) : value(value), suit(suit) {}

Card::Card(int value, std::string suit) : value(value),
                                          suit(stringToSuit(suit)) {}

Card::Card(std::string value, Suit suit) : value(stringToValue(value)),
                                           suit(suit) {}

Card::Card(std::string value, std::string suit) : value(stringToValue(value)),
                                                  suit(stringToSuit(suit)) {}

Card::Card(const Card &other) : value(other.value), suit(other.suit) {}

std::map<std::string, int> Card::buildStringToValueLookup()
{
  std::map<std::string, int> map = {
      {"one", 1},
      {"two", 2},
      {"three", 3},
      {"four", 4},
      {"five", 5},
      {"six", 6},
      {"seven", 7},
      {"eight", 8},
      {"nine", 9},
      {"ten", 10},
      {"eleven", 11},
      {"twelve", 12},
      {"thirteen", 13},

      {"a", 1},
      {"ace", 1},
      {"x", 10},
      {"j", 11},
      {"jack", 11},
      {"q", 12},
      {"queen", 12},
      {"k", 13},
      {"king", 13},
  };

  for (int i = 1; i <= 13; i++)
  {
    map[std::to_string(i)] = i;
  }

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

  return new Card(stringToValue(value), stringToSuit(suit));
}

Card::Suit Card::stringToSuit(const std::string &str)
{
  try
  {
    return stringToSuitLookup.at(str);
  }
  catch (const std::out_of_range &e)
  {
    throw std::invalid_argument("recieved invalid suit representation");
  }
}

int Card::stringToValue(const std::string &str)
{
  try
  {
    return stringToValueLookup.at(str);
  }
  catch (const std::out_of_range &e)
  {
    throw std::invalid_argument("received invalid value representation");
  }
}

std::string Card::suitToString(Suit suit)
{
  return suitToStringLookup.at(suit);
}

std::string Card::suitToSymbol(Suit suit)
{
  return suitToSymbolLookup.at(suit);
}

std::string Card::valueToString(int val)
{
  return valueToStringLookup.at(val);
}

std::string Card::valueToSymbol(int val)
{
  return valueToSymbolLookup.at(val);
}

std::string Card::toString()
{
  return valueToStringLookup.at(value) + " of " + suitToStringLookup.at(suit);
}

std::string Card::toSymbol()
{
  // TODO: test
  return valueToSymbol(value) + suitToSymbol(suit);
}