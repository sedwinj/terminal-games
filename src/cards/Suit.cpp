#include "Suit.hpp"

auto Suit::suits = Suit::buildSuits();

Suit::Suit(std::string name, Color color) : name(name), color(color) {}

const std::vector<Suit> &Suit::buildSuits()
{
  auto suits = std::vector<Suit>();
  suits.push_back(Suit("Hearts", Color::RED));
  suits.push_back(Suit("Diamonds", Color::RED));
  suits.push_back(Suit("Clubs", Color::BLACK));
  suits.push_back(Suit("Spades", Color::BLACK));

  return suits;
}

Suit::Color Suit::getColor()
{
  return this->color;
}

std::string Suit::getName()
{
  return this->name;
}

const std::vector<Suit> &Suit::getSuits()
{
  return suits;
}

std::string Suit::toString()
{
  return getName();
}