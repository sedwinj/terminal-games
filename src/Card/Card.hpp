#include <memory>
#include <string>
#include <vector>

class Card
{
public:
  enum Suit
  {
    HEARTS,
    CLUBS,
    DIAMONDS,
    SPADES
  };

  enum Color
  {
    RED,
    BLACK
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
  enum Type
  {
    CHAR = 0,
    STR = 1,
    SYMBOL = 2
  };

  Suit suit;
  int value;

  static Suit parseSuit(std::string suit);
  static int parseValue(std::string value);
  static std::string suitToString(Suit suit);
  static std::string valueToString(int value);
};