#pragma once

#include <algorithm>
#include <map>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "src/Util.hpp"

class Card
{
public:
  static const int MAXVALUE = 13;
  enum Suit
  {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
  };

  static std::vector<Card *> newDeck();

  /*  Parses a string and returns the card it represents. Case-insensitive.
   *  Accepted input formats are:
   *  - symbolic form (e.g.: "QH", "12H")
   *  - symbolic form with a space (e.g.: "Q H", "12 H")
   *  - word form (e.g.: "queen of hearts", "12 of hearts",
   *    "twelve of hearts")
   *  - several hybridizations of the above forms
   *
   *  The symbols "A", "X" (10), "J", "Q", and "K" can be used instead of a
   *  value.
   */
  static Card *parse(std::string str);

  // Constructors
  Card(int value, Suit suit);
  Card(int value, std::string suit);
  Card(std::string value, Suit suit);
  Card(std::string value, std::string suit);

  // Copy constructor
  Card(const Card &other);

  static std::vector<Card *> buildDeck();
  static std::vector<Card *> buildShuffledDeck(int seed);

  Suit getSuit() const;
  int getValue() const;
  bool isBlack() const;
  bool isRed() const;
  bool operator==(const Card &other) const;
  bool operator!=(const Card &other) const;
  std::string toString();
  std::string toSymbol();

private:
  int value;
  Suit suit;

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