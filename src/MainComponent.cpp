#include "MainComponent.hpp"

MainComponent::MainComponent() : freeCell(FreeCell(FreeCell::Board(std::vector<Card *>()))) {}

int MainComponent::run()
{
  std::cout << freeCell.boardToString() << std::endl;

  return EXIT_SUCCESS;
}