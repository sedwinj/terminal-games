#pragma once

#include <stdexcept>

class IllegalGameMove : public std::exception
{
public:
  IllegalGameMove(std::string message);
  const char *what();

private:
  const char *message;
};