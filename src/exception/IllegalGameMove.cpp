#include "IllegalGameMove.hpp"

IllegalGameMove::IllegalGameMove(std::string message) : message(message.c_str()) {}

const char *IllegalGameMove::what()
{
  return message;
}