#pragma once

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "src/Util.hpp"

class Card
{
public:
  enum Suit
  {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
  };

  enum Color
  {
    BLACK,
    RED
  };

  static std::vector<Card *> newDeck();

  /*  Parses a string and converts it to a card. Accepted formats are of the
   *  form:
   *  - <charvalue><charnumber> (e.g.: "QH", "12H")
   *  - <charvalue> <charnumber> (e.g.: "Q H", "12 H")
   *  - <value> of <number> (e.g.: "queen of hearts", "12 of hearts",
   *    "twelve of hearts")
   */
  static Card *parse(std::string str);

  // Constructors
  Card(int value, Suit suit);
  Card(int value, std::string suit);
  Card(std::string value, Suit suit);
  Card(std::string value, std::string suit);

  // Copy constructor
  Card(const Card &other);

  Suit getSuit() const;
  int getValue() const;
  bool operator==(const Card &other) const;
  bool operator!=(const Card &other) const;
  std::string toString();
  std::string toSymbol();

private:
  Suit suit;
  int value;

  static const std::map<std::string, Suit> stringToSuitLookup;
  static const std::map<Suit, std::string> suitToStringLookup;
  static const std::map<Suit, std::string> suitToSymbolLookup;

  static const std::map<std::string, int> stringToValueLookup;
  static const std::map<int, std::string> valueToStringLookup;
  static const std::map<int, std::string> valueToSymbolLookup;

  static std::map<std::string, int> buildStringToValueLookup();
  static Suit stringToSuit(const std::string &str);
  static int stringToValue(const std::string &str);
  static std::string suitToString(Suit suit);
  static std::string suitToSymbol(Suit suit);
  static std::string valueToString(int val);
  static std::string valueToSymbol(int val);
};