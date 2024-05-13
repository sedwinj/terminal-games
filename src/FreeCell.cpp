#include "FreeCell.hpp"

const std::string FreeCell::Board::CARD_SLOT = "[]";
const std::string FreeCell::Board::NO_CARD = "  ";
const std::string FreeCell::Board::SEPARATOR = " ";
const std::string FreeCell::Board::SPACER(FreeCell::Board::CARD_SLOT.size() + FreeCell::Board::SEPARATOR.size(), ' ');

FreeCell::Board::Board(std::vector<Card *> deck)
{
  // TODO: test
  std::vector<Card *>::iterator it = deck.begin();
  for (int col = 0; it != deck.end(); col = ++col % COLUMNS)
  {
    columns[col].push_back(*it++);
  }

  freeCells.fill(nullptr);
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
  for (int col = 0; col < COLUMNS; col++)
  {
    columns[col] = std::vector<Card *>();
    for (auto card : columns[col])
    {
      columns.back().push_back(new Card(*card));
    }
  }
}

FreeCell::Board::~Board()
{
  for (auto foundation : foundations)
    Util::deleteAll(foundation);

  for (Card *card : freeCells)
    delete card;

  for (auto column : columns)
    Util::deleteAll(column);
}

std::string FreeCell::Board::rowToString(int row)
{
  std::string rowStr = SPACER;
  for (int col = 0; col < columns.size(); col++)
  {
    if (columns[col].size() > row)
    {
      rowStr += columns[col][row]->toSymbol();
    }
    else
    {
      rowStr += NO_CARD;
    }

    if (col < columns.size() - 1)
    {
      rowStr += SEPARATOR;
    }
  }
  rowStr += SPACER + "\n";

  return rowStr;
}

std::string FreeCell::Board::toString()
{
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
      boardString += CARD_SLOT;
    }
    boardString += SEPARATOR;
  }
  boardString += SPACER + SPACER;
  for (int idx = 0; idx < FREE_CELLS; idx++)
  {
    if (freeCells[idx] != nullptr)
    {
      boardString += freeCells[idx]->toSymbol();
    }
    else
    {
      boardString += CARD_SLOT;
    }

    if (idx < FREE_CELLS - 1)
    {
      boardString += SEPARATOR;
    }
  }
  boardString += "\n";

  // Create body lines
  int rowNum = 0;
  std::string nextRow = rowToString(rowNum++);
  while (Util::stringTrim(nextRow) != "")
  {
    boardString += nextRow;
    nextRow = rowToString(rowNum++);
  }

  return boardString;
}

FreeCell::FreeCell() : FreeCell(std::random_device{}()) {}

FreeCell::FreeCell(int seed) : seed(seed),
                               board(Board(Card::buildShuffledDeck(seed))) {}

FreeCell::FreeCell(const Board &board) : board(Board(board)) {}

void FreeCell::setSeed(int seed)
{
  this->seed = seed;
}