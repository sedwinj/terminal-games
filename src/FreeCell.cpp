#include "FreeCell.hpp"

using Board = FreeCell::Board;

const std::string Board::CARD_SLOT = "[]";
const std::string Board::NO_CARD = "  ";
const std::string Board::SEPARATOR = " ";
const std::string Board::SPACER(Board::CARD_SLOT.size() + Board::SEPARATOR.size(), ' ');

const std::map<std::string, Board::Location> FreeCell::stringToLocationLookup = {
    {"foundation", Board::Location::FOUNDATIONS},

    {"clubs", Board::Location::FOUNDATIONS},
    {"diamonds", Board::Location::FOUNDATIONS},
    {"hearts", Board::Location::FOUNDATIONS},
    {"spades", Board::Location::FOUNDATIONS},

    {"c", Board::Location::FOUNDATIONS},
    {"d", Board::Location::FOUNDATIONS},
    {"h", Board::Location::FOUNDATIONS},
    {"s", Board::Location::FOUNDATIONS},

    {"freecell", Board::Location::FREE_CELLS},
    {"freecells", Board::Location::FREE_CELLS},
    {"free cell", Board::Location::FREE_CELLS},
    {"free cells", Board::Location::FREE_CELLS},
    {"free", Board::Location::FREE_CELLS},
    {"[]", Board::Location::FREE_CELLS},
};

Board::Board() {}

Board::Board(std::vector<Card *> deck)
{
  std::vector<Card *>::iterator it = deck.begin();
  for (int col = 0; it != deck.end(); ++col %= CASCADE_COUNT)
  {
    cascades[col].push_back(*it++);
  }

  freeCells.fill(nullptr);
}

Board::Board(const Board &other)
{
  // Foundations
  for (int idx; idx < FOUNDATION_SIZE; idx++)
  {
    foundations[idx] = std::vector<Card *>();
    for (auto card : foundations[idx])
    {
      foundations[idx].push_back(new Card(*card));
    }
  }

  // FreeCells
  for (size_t idx = 0; idx < FREE_CELL_SIZE; idx++)
  {
    Card *card = other.freeCells[idx];
    freeCells[idx] = card != nullptr ? new Card(*card) : nullptr;
  }

  // Cascades
  for (int col = 0; col < CASCADE_COUNT; col++)
  {
    cascades[col] = std::vector<Card *>();
    for (auto card : other.cascades[col])
    {
      cascades[col].push_back(new Card(*card));
    }
  }
}

Board::~Board()
{
  for (auto foundation : foundations)
    Util::deleteAll(foundation);

  for (Card *card : freeCells)
    delete card;

  for (auto column : cascades)
    Util::deleteAll(column);
}

bool Board::columnsEqual(const Cascades &col1, const Cascades &col2)
{
  for (size_t idx = 0; idx < col1.size(); idx++)
  {
    if (col1[idx].size() != col2[idx].size())
    {
      return false;
    }
    for (size_t jdx = 0; jdx < col1[idx].size(); jdx++)
    {
      if (*col1[idx][jdx] != *col2[idx][jdx])
      {
        return false;
      }
    }
  }
  return true;
}

bool Board::equal(const Board &other) const
{
  return foundations == other.foundations &&
         freeCells == other.freeCells &&
         columnsEqual(cascades, other.cascades);
}

Board::SearchResult Board::find(const Card &card) const
{
  // TODO: test
  SearchResult res;

  // Search foundations
  if ((int)foundations[card.getSuit()].size() >= card.getValue())
  {
    res.found = true;
    res.location = FOUNDATIONS;
    res.position.push_back(card.getValue() - 1);
    res.accessible = (int)foundations[card.getSuit()].size() == card.getValue() - 1;

    return res;
  }

  // Search free cells
  for (size_t idx = 0; idx < freeCells.size(); idx++)
  {
    if (*freeCells[idx] == card)
    {
      res.found = true;
      res.location = FREE_CELLS;
      res.position.push_back(idx);
      res.accessible = true;

      return res;
    }
  }

  // Search cascades
  for (size_t idx = 0; idx < cascades.size(); idx++)
  {
    for (size_t jdx = 0; jdx < cascades[idx].size(); jdx++)
    {
      if (*cascades[idx][jdx] == card)
      {
        res.found = true;
        res.location = CASCADES;
        res.position.push_back(idx);
        res.position.push_back(jdx);
        res.accessible = (size_t)freeCellCount >= cascades[idx].size() - jdx &&
                         isValidTableau(std::vector<Card *>(cascades[idx].begin() + jdx, cascades[idx].end()));

        return res;
      }
    }
  }

  return res;
}

bool Board::operator==(const Board &other) const
{
  return this->equal(other);
}

bool Board::operator!=(const Board &other) const
{
  return !this->equal(other);
}

Board Board::parse(const std::string &str)
{
  // TODO: test

  std::vector<std::string> rows = Util::stringSplit(str, "\n");
  std::transform(rows.begin(), rows.end(), rows.begin(), Util::stringTrim);

  // Create a sparse 2D array of cards
  std::vector<std::vector<Card *>> cards;
  cards.push_back(std::vector<Card *>());
  for (std::string card : Util::stringSplit(rows[0], " "))
  {
    if (card == "")
    {
      continue;
    }

    if (card == CARD_SLOT)
    {
      cards.back().push_back(nullptr);
      continue;
    }

    cards.back().push_back(Card::parse(card));
  }
  for (size_t idx = 1; idx < rows.size(); idx++)
  {
    cards.push_back(std::vector<Card *>());
    std::vector<std::string> row = Util::stringSplit(rows[idx], SEPARATOR);
    for (size_t jdx = 0; jdx < row.size(); jdx++)
    {
      if (row[jdx] == "")
      {
        cards.back().push_back(nullptr);
        idx += CARD_SLOT.size();
        continue;
      }

      cards.back().push_back(Card::parse(row[jdx]));
    }
  }

  // Define logic to check if a card already exists in the board.
  std::array<bool, Card::DECK_SIZE> exists;
  exists.fill(false);
  auto existenceCheck = [&exists](Card *card) -> void
  {
    if (!card)
    {
      return;
    }

    int pos = card->getSuit() * Card::MAXVALUE + card->getValue();
    if (exists[pos] == true)
    {
      throw std::invalid_argument(card->toString() + "already exists");
    }

    exists[pos] = true;
  };

  // Convert 2D card array into a board.
  Board board = Board();
  for (size_t idx = 0; idx < CASCADE_COUNT; idx++)
  {
    Card *card = cards[0][idx];
    if (card == nullptr)
    {
      continue;
    }

    Card::Suit suit = card->getSuit();
    for (int value = 1; value < card->getValue(); value++)
    {
      Card *impliedCard = new Card(value, suit);
      existenceCheck(impliedCard);
      board.foundations[suit].push_back(impliedCard);
    }
    board.foundations[suit].push_back(card);
  }

  for (size_t idx = 1; idx < FREE_CELL_SIZE; idx++)
  {
    Card *card = cards[0][FOUNDATION_SIZE + idx];
    existenceCheck(card);
    board.freeCells[idx] = card;
  }

  for (size_t idx = 0; idx < cards.size(); idx++)
  {
    std::vector<Card *> row = cards[idx];
    for (size_t jdx = 0; jdx < cards.size(); jdx++)
    {
      Card *card = cards[idx][jdx];
      existenceCheck(card);
      board.cascades[jdx].push_back(card);
    }
  }

  return board;
}

std::string Board::rowToString(size_t row) const
{
  std::string rowStr = SPACER;
  for (size_t col = 0; col < cascades.size(); col++)
  {
    if (cascades[col].size() > row)
    {
      rowStr += cascades[col][row]->toSymbol();
    }
    else
    {
      rowStr += row > 0 ? NO_CARD : CARD_SLOT;
    }

    if (col < cascades.size() - 1)
    {
      rowStr += SEPARATOR;
    }
  }
  rowStr += SPACER + "\n";

  return rowStr;
}

Board::SearchResult Board::find(std::string str)
{
  // TODO: test

  // Is there a nicer way to do this?

  str = Util::stringTrim(str);
  SearchResult res;

  // Handles all card targets.
  try
  {
    Card card = Card(str);
    return find(card);
  }
  catch (const std::invalid_argument &e)
  {
    // Do nothing
  }

  // Handles general foundation and free cell targets.
  auto finder = stringToLocationLookup.find(Util::stringLower(str));
  if (finder != stringToLocationLookup.end())
  {
    res.found = true;
    res.location = finder->second;

    return res;
  }

  // Handles lookup of general empty cascade
  if (str == "c")
  {
    for (size_t idx = 0; idx < cascades.size(); idx++)
    {
      if (cascades[idx].size() == 0)
      {
        res.found = true;
        res.location = CASCADES;
        res.position.push_back(idx);
        res.accessible = true;

        return res;
      }
    }
  }

  // Handles insertion to specific cascade
  if (str[0] == 'c' && Util::isNumeric(str.substr(1)))
  {
    int cascade = std::atoi(str.substr(1).c_str());
    if (cascades[cascade].size() == 0)
    {
      res.found = true;
      res.location = CASCADES;
      res.position.push_back(cascade);
      res.accessible = true;

      return res;
    }
  }

  throw std::invalid_argument("Could not parse target location (\"" + str + "\")");
}

void Board::move(Location cardLoc, std::vector<int> cardPos,
                 Location targetLoc, std::vector<int> targetPos)
{
  // TODO: test
  std::vector<Card *> buffer;

  // Remove card(s)
  if (cardLoc == Location::FOUNDATIONS)
  {
    buffer.push_back(foundations[cardPos[0]].back());
    foundations[cardPos[0]].pop_back();
  }
  else if (cardLoc == Location::FREE_CELLS)
  {
    buffer.push_back(freeCells[cardPos[0]]);
    freeCells[cardPos[0]] = nullptr;
  }
  else
  {
    while (cascades[cardPos[0]].size() <= (size_t)cardPos[1])
    {
      buffer.push_back(cascades[0].back());
      cascades[0].pop_back();
    }
  }

  // Place card(s)
  if (targetLoc == Location::FOUNDATIONS)
  {
    foundations[targetPos[0]].push_back(buffer.back());
    buffer.pop_back();
  }
  else if (targetLoc == Location::FREE_CELLS)
  {
    freeCells[targetPos[0]] = buffer.back();
    buffer.pop_back();
  }
  else
  {
    while (buffer.size() > 0)
    {
      cascades[targetPos[0]].push_back(buffer.back());
      buffer.pop_back();
    }
  }
}

std::string Board::toString() const
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
  for (size_t idx = 0; idx < FREE_CELL_SIZE; idx++)
  {
    if (freeCells[idx] != nullptr)
    {
      boardString += freeCells[idx]->toSymbol();
    }
    else
    {
      boardString += CARD_SLOT;
    }

    if (idx < FREE_CELL_SIZE - 1)
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

FreeCell::FreeCell(int seed) : board(Board(Card::buildShuffledDeck(seed))),
                               seed(seed) {}

FreeCell::FreeCell(const Board &board) : board(Board(board)) {}

std::string FreeCell::boardToString() const
{
  return board.toString();
}

bool FreeCell::isValidTableau(const std::vector<Card *> &tableau)
{
  Card *lastCard = nullptr;
  for (Card *card : tableau)
  {
    if (!lastCard)
    {
      lastCard = card;
      continue;
    }

    if (card->isRed() == lastCard->isRed() ||
        card->getValue() != lastCard->getValue() - 1)
    {
      return false;
    }

    lastCard = card;
  }

  return true;
}

void FreeCell::move(const std::string &cardStr, std::string target)
{
  // TODO: test
  Card card = Card(cardStr);
  Board::SearchResult res = board.find(card);
  if (!res.accessible)
  {
    throw IllegalGameMove("Card to move is inaccessible");
  }

  Board::SearchResult targetRes = board.find(target);

  /*
   * Throw IllegalGameMove if card to move to  a foundation or free cell isn't
   * immediately accessible
   */
  if (res.location == Board::Location::CASCADES &&
      (size_t)res.position[1] != board.cascades[res.position[0]].size() - 1 &&
      (targetRes.location == Board::Location::FOUNDATIONS ||
       targetRes.location == Board::Location::FREE_CELLS))
  {
    throw IllegalGameMove("Card is not immediately accessible.");
  }

  // Move card to resepective foundation
  if (targetRes.location == Board::Location::FOUNDATIONS)
  {
    if (card.getValue() != board.foundations[card.getSuit()].back()->getValue() + 1)
    {
      throw IllegalGameMove("Card cannot be placed on foundation.");
    }

    std::vector<int> targetPos;
    targetPos.push_back(card.getSuit());
    board.move(res.location, res.position, targetRes.location, targetPos);
  }

  // Move card to a free cell
  else if (targetRes.location == Board::Location::FREE_CELLS)
  {
    if (board.freeCellCount == 0)
    {
      throw IllegalGameMove("There is no free cell to place the card.");
    }

    std::vector<int> targetPos;
    targetPos.push_back(0);
    for (; board.freeCells[targetPos[0]] != nullptr; targetPos[0]++)
    {
      // Do nothing. Increment targetPos.
    }

    board.move(res.location, res.position, targetRes.location, targetPos);
  }

  // Move card to a cascade
  else
  {
    board.move(res.location, res.position, targetRes.location, targetRes.position);
  }
}