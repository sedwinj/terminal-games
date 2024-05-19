#pragma once

#include <stdexcept>

class IllegalGameMove : public std::exception
{
public:
  IllegalGameMove(char *message);
  char *what();

private:
  char *message;
};