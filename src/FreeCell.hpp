#pragma once

#include <array>
#include <random>
#include <string>

#include "Card.hpp"
#include "Util.hpp"

class FreeCell
{
public:
  static const int COLUMNS = 8;
  static const int FOUNDATIONS = 4;
  static const int FREE_CELLS = 4;

  class Board
  {
  public:
    std::array<std::vector<Card *>, FOUNDATIONS> foundations;
    std::array<Card *, FREE_CELLS> freeCells;
    std::vector<std::vector<Card *>> columns;

    Board();

    // Creates a deep copy of the input.
    Board(const Board &other);
  };

  // Initializes a new FreeCell object with a random seed.
  FreeCell();

  // Initializes a new FreeCell object from a specific seed.
  FreeCell(int seed);

  // Initializes a new FreeCell object from an existing board struct;
  FreeCell(const Board &board);

  std::string boardToString();

  static Board createBoard(std::vector<Card *> deck);

  /*
   *  Attempts to move the specified card (and the tablueau below it) to the
   *  specified position, according to FreeCell game rules. Moves the card(s)
   *  and returns true if the action was valid and successful. Has no effect and
   *  returns false otherwise.
   */
  bool move(std::string card, std::string position);

  void setSeed(int seed);

private:
  Board board;
  int seed;

  // Returns true if the input is a valid tableau.
  bool isValidTableau(std::vector<Card *> tableau);

  std::string boardRowToString(int row);
};