#pragma once

#include <array>
#include <random>
#include <string>

#include "Card.hpp"
#include "Util.hpp"

class FreeCell
{
public:
  static const int CASCADE_COUNT = 8;
  static const int FOUNDATION_SIZE = 4;
  static const int FREE_CELL_SIZE = 4;

  class Board
  {
    friend class FreeCell;

  public:
    typedef std::array<std::vector<Card *>, CASCADE_COUNT> Cascades;

    std::array<std::vector<Card *>, FOUNDATION_SIZE> foundations;
    std::array<Card *, FREE_CELL_SIZE> freeCells;
    Cascades cascades;

    Board(std::vector<Card *> deck);

    // Creates a deep copy of the input.
    Board(const Board &other);

    ~Board();

    bool equal(const Board &other) const;

    bool operator==(const Board &other) const;

    bool operator!=(const Board &other) const;

    std::string toString() const;

  private:
    static const std::string CARD_SLOT;
    static const std::string NO_CARD;
    static const std::string SEPARATOR;
    static const std::string SPACER;

    enum Location
    {
      CASCADES,
      FOUNDATIONS,
      FREE_CELLS
    };

    struct SearchResult
    {
      bool found = false;

      Location location;
      std::vector<int> position;
      bool accessible;
    };

    /*
     * Returns true if two sets of cascades contain equal cards in the equal
     * positions.
     */
    static bool columnsEqual(const Cascades &col1, const Cascades &col2);

    SearchResult find(const Card &card) const;

    /*
     * Parses the input to find a suitable location. The returned SearchResult
     * will lack position data if the input parses to the foundations or free
     * cells in general.
     *
     * Throws an invalid_argument exception on failed parse.
     */
    SearchResult find(std::string str);

    std::string rowToString(size_t row) const;
  };

  // Initializes a new FreeCell object with a random seed.
  FreeCell();

  // Initializes a new FreeCell object from a specific seed.
  FreeCell(int seed);

  // Initializes a new FreeCell object from an existing FreeCell::Board;
  FreeCell(const Board &board);

  std::string boardToString() const;

  /*
   *  Attempts to move the specified card (and the tablueau below it) to the
   *  specified position, according to FreeCell game rules. Moves the card(s)
   *  and returns true if the action was valid and successful. Has no effect and
   *  returns false otherwise.
   */
  bool move(const std::string &card, std::string position);

private:
  static const std::map<std::string, Board::Location> stringToLocationLookup;

  Board board;
  int seed;
};