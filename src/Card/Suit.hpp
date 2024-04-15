#pragma once

#include <string>
#include <vector>

class Suit
{
public:
  enum Color
  {
    RED,
    BLACK
  };

  Color getColor();
  std::string getName();
  std::string toString();
  static const std::vector<Suit> &getSuits();

  static const std::vector<Suit> &buildSuits();

private:
  const std::string name;
  const Color color;
  static std::vector<Suit> suits;

  Suit(std::string name, Color color);
};