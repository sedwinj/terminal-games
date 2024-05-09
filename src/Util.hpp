#pragma once

#include <string>
#include <vector>

namespace Util
{
  template <typename T>
  bool contains(const std::vector<T> &array, const T &value);
  inline std::string stringLower(const std::string &in);
  inline std::vector<std::string> stringSplit(const std::string &str);
  inline std::vector<std::string> stringSplit(const std::string &str, const std::string &delim);
  inline std::string stringTrim(const std::string &str);

  // Returns true if the value is in the array, and false otherwise.
  template <typename T>
  inline bool contains(const std::vector<T> &array, const T &value)
  {
    // TODO: test
    for (int idx = 0; idx < array.size(); idx++)
    {
      if (value == array[idx])
      {
        return true;
      }
    }
    return false;
  }

  // Returns a copy of the string with all letters converted to lowercase.
  inline std::string stringLower(const std::string &in)
  {
    std::string out = in;
    for (int idx = 0; idx < out.size(); idx++)
    {
      if ('A' <= out[idx] && out[idx] <= 'Z')
      {
        out[idx] += 'a' - 'A';
      }
    }
    return out;
  }

  // Splits the string, using commas as a delimiter.
  inline std::vector<std::string> stringSplit(const std::string &str)
  {
    return stringSplit(str, ",");
  }

  // Splits the string using the specified delimiter.
  inline std::vector<std::string> stringSplit(const std::string &str, const std::string &delim)
  {
    std::vector<std::string> split;
    int left = 0;
    int right = str.find(delim, left);
    while (right != std::string::npos)
    {
      split.push_back(str.substr(left, right - left));
      left = right + delim.size();
      right = str.find(delim, left);
    }
    split.push_back(str.substr(left));

    return split;
  }

  // Returns a copy of the input without leading and trailing whitespace characters.
  inline std::string stringTrim(const std::string &str)
  {
    // TODO: test
    const char _whitespace[] = {' ', '\n', '\t'};
    const auto WHITESPACE = std::vector<char>(_whitespace, _whitespace + 3);

    int start = 0;
    for (; start < str.size(); start++)
    {
      if (!contains<char>(WHITESPACE, str[start]))
      {
        break;
      }
    }

    int end = str.size() - 1;
    for (; end >= 0; end--)
    {
      if (!contains<char>(WHITESPACE, str[end]))
      {
        end++;
        break;
      }
    }

    return str.substr(start, end - start);
  }
}