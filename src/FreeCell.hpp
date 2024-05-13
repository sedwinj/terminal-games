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

  typedef struct Board
  {
    std::array<std::vector<Card *>, FOUNDATIONS> foundations;
    std::array<Card *, FREE_CELLS> freeCells;
    std::vector<std::vector<Card *>> columns;

    inline Board() {}

    // Performs a deep copy of rhs and assigns it to lhs.
    inline Board(const Board &other)
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
  } Board;

  // Initializes a new FreeCell object from a seeded random number generator.
  FreeCell(std::mt19937 rng);

  // Initializes a new FreeCell object from an existing board struct;
  FreeCell(const Board &board);

  std::string boardToString();

  /*
   *  Attempts to move the specified card (and the tablueau below it) to the
   *  specified position, according to FreeCell game rules. Moves the card(s)
   *  and returns true if the action was valid and successful. Has no effect and
   *  returns false otherwise.
   */
  bool move(std::string card, std::string position);

  void setGenerator(std::mt19937 rng);

private:
  Board board;
  std::mt19937 rng;

  void generateBoard();

  // Returns true if the input is a valid tableau.
  bool isValidTableau(std::vector<Card *> tableau);

  std::string boardRowToString(int row);
};