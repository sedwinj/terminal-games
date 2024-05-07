#include "Card.hpp"

Card::Card(int value, Suit suit) : value(value), suit(suit) {}

Card::Card(int value, std::string suit) : value(value),
                                          suit(parseSuit(suit)) {}

Card::Card(std::string value, Suit suit) : value(parseValue(value)),
                                           suit(suit) {}

Card::Card(std::string value, std::string suit) : value(parseValue(value)),
                                                  suit(parseSuit(suit)) {}

Card::Card(const Card &other) : value(other.value), suit(other.suit) {}

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
  // TODO: implement
}

Card::Suit Card::parseSuit(std::string suit)
{
  // TODO: implement
}

int Card::parseValue(std::string value)
{
  // TODO; implement
}

std::string Card::toString()
{
  return valueToString(value) + " of " + suitToString(suit);
}

std::string Card::toSymbol()
{
  // TODO: implement
}

std::string Card::suitToString(Suit suit)
{
  switch (suit)
  {
  case HEARTS:
    return "Hearts";
  case CLUBS:
    return "Clubs";
  case DIAMONDS:
    return "Diamonds";
  case SPADES:
    return "Spades";
  }
}

std::string Card::valueToString(int value)
{
  std::string valueString;
  switch (value)
  {
  case 1:
    return "Ace";
  case 2:
    return "Two";
  case 3:
    return "Three";
  case 4:
    return "Four";
  case 5:
    return "Five";
  case 6:
    return "Six";
  case 7:
    return "Seven";
  case 8:
    return "Eight";
  case 9:
    return "Nine";
  case 10:
    return "Ten";
  case 11:
    return "Jack";
  case 12:
    return "Queen";
  case 13:
    return "King";
  default:
    return std::to_string(value);
  }
}