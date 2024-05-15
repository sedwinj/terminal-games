#pragma once

#include <iostream>

#include "FreeCell.hpp"

class MainComponent
{
public:
  MainComponent();
  int run();

private:
  FreeCell freeCell;
};