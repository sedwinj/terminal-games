#include "FreeCell.hpp"

FreeCell::FreeCell() : FreeCell(std::random_device{}()) {}

FreeCell::FreeCell(int seed)
{
  // TODO: test
  setSeed(seed);
  generateBoard();
}

FreeCell::FreeCell(const Board &board)
{
  this->board = Board(board);
}

std::string FreeCell::boardRowToString(int row)
{
  // TODO: implemenet
}

std::string FreeCell::boardToString()
{
  // TODO: implement
  const std::string SEPARATOR = " ";
  const std::string NO_CARD = "[]";

  std::string boardString = "";

  // Create foundation and freecell line
  for (auto foundation : board.foundations)
  {
    if (foundation.size() > 0)
    {
      boardString += foundation.back()->toSymbol();
    }
    else
    {
      boardString += NO_CARD;
    }
    boardString += SEPARATOR;
  }
  for (int idx = 0; idx < FREE_CELLS; idx++)
  {
    if (board.freeCells[idx] != nullptr)
    {
      boardString += board.freeCells[idx]->toSymbol();
    }
    else
    {
      boardString += NO_CARD;
    }

    if (idx < FREE_CELLS - 1)
    {
      boardString += SEPARATOR;
    }
  }

  // TODO: continue 2024-05-12 16:47
  int rowNum = 0;
  std::string nextRow = boardRowToString(rowNum++);
  while (Util::stringTrim(nextRow) != "")
  {
    nextRow = boardRowToString(rowNum++);
  }
}

void FreeCell::generateBoard()
{
  auto deck = Card::buildShuffledDeck(seed);

  int column = 0;
}

void FreeCell::setSeed(int seed)
{
  this->seed = seed;
}