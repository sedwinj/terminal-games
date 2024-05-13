#include "FreeCell.hpp"

FreeCell::Board::Board(std::vector<Card *> deck)
{
  // TODO: test
  std::vector<Card *>::iterator it = deck.begin();
  for (int col = 0; it != deck.end(); col = ++col % COLUMNS)
  {
    columns[col].push_back(*it++);
  }
}

FreeCell::Board::Board(const Board &other)
{
  // Foundations
  for (int idx; idx < FOUNDATIONS; idx++)
  {
    foundations[idx] = std::vector<Card *>();
    for (auto card : foundations[idx])
    {
      foundations[idx].push_back(new Card(*card));
    }
  }

  // FreeCells
  for (int idx = 0; idx < FREE_CELLS; idx++)
  {
    freeCells[idx] = new Card(*other.freeCells[idx]);
  }

  // Columns
  for (auto column : columns)
  {
    columns.push_back(std::vector<Card *>());
    for (auto card : column)
    {
      columns.back().push_back(new Card(*card));
    }
  }
}

std::string FreeCell::Board::rowToString(int row)
{
  // TODO: implement
}

std::string FreeCell::Board::toString()
{
  // TODO: implement
  const std::string SEPARATOR = " ";
  const std::string NO_CARD = "[]";

  std::string boardString = "";

  // Create foundation and freecell line
  for (auto foundation : foundations)
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
    if (freeCells[idx] != nullptr)
    {
      boardString += freeCells[idx]->toSymbol();
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
  std::string nextRow = rowToString(rowNum++);
  while (Util::stringTrim(nextRow) != "")
  {
    nextRow = rowToString(rowNum++);
  }
}

FreeCell::FreeCell() : FreeCell(std::random_device{}()) {}

FreeCell::FreeCell(int seed) : seed(seed),
                               board(Board(Card::buildShuffledDeck(seed))) {}

FreeCell::FreeCell(const Board &board) : board(Board(board)) {}

void FreeCell::setSeed(int seed)
{
  this->seed = seed;
}