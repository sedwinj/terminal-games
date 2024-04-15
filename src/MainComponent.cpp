#include "MainComponent.hpp"

int MainComponent::main(int argc, char **argv)
{
  // auto suits = Suit::getSuits();
  auto suits = Suit::buildSuits();
  for (Suit suit : suits)
  {
    std::cout << suit.toString() << '\n';
  }
  std::cout << std::endl;

  return EXIT_SUCCESS;
}