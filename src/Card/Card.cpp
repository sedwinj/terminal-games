#include "Card.hpp"

Card::Card(Suit suit, int value) : suit(suit),
                                   value(value),
                                   black(suit == CLUBS || suit == SPADES) {}

Suit Card::getSuit()
{
  return suit;
}

int Card::getValue()
{
  return value;
}

std::string Card::toString()
{
  std::string valueString;
  switch (value)
  {
  case 1:
    valueString = "Ace";
    break;
  case 11:
    valueString = "Jack";
    break;
  case 12:
    valueString = "Queen";
    break;
  case 13:
    valueString = "King";
  default:
    valueString = std::to_string(value);
  }

  std::string suitString;
  switch (suit)
  {
  case HEARTS:
    suitString = ""
  }

  return
}