#include <string>
#include <vector>

namespace Util
{
  // Returns true if the value is in the array, and false otherwise.
  template <typename T>
  bool contains(const std::vector<T> &array, const T &value);

  // Returns a copy of the input without leading and trailing whitespace characters.
  std::string stringTrim(const std::string &str);

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
        start--;
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