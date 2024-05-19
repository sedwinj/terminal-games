#pragma once

#include <array>
#include <random>
#include <string>

#include "Card.hpp"
#include "Util.hpp"
#include "exception/IllegalGameMove.hpp"

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

    int freeCellCount = FREE_CELL_SIZE;

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
     * Parses the input to find a suitable location.
     *
     * The returned SearchResult will lack position data and accessibility will
     * be undefined if the input parses to the foundations or free cells.
     *
     * Throws an invalid_argument exception on failed parse.
     */
    SearchResult find(std::string str);

    /*
     * Moves the card (and any cards beneath) from one position to another.
     * Assumes all inputs are valid.
     *
     * Undefined behavior for invalid inputs and moves.
     */
    void move(Location cardLoc, std::vector<int> cardPos, Location targetLoc,
              std::vector<int> targetPos);

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
   *  if the action was valid and successful.
   *
   * Throws IllegalGameMove if the action is invalid. Does not alter the board
   * if this is the case.
   */
  void move(const std::string &card, std::string target);

private:
  static const std::map<std::string, Board::Location> stringToLocationLookup;

  Board board;
  int seed;

  static bool isValidTableau(const std::vector<Card *> &tableau);
};