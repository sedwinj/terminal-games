#include "IllegalGameMove.hpp"

IllegalGameMove::IllegalGameMove(char *message) : message(message) {}

char *IllegalGameMove::what()
{
  return message;
}