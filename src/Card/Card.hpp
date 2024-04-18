#include <string>

class Card
{
public:
  Card(Suit suit, int value);
  Suit getSuit();
  int getValue();
  std::string toString();

private:
  const Suit suit;
  const int value;
  const bool black;
};