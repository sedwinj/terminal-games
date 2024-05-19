#pragma once

#include <string>
#include <vector>

namespace Util
{
  template <typename T>
  inline bool contains(const std::vector<T> &array, const T &value);
  template <class T>
  inline void deletePtr(T *&object);
  template <class T>
  inline void deleteAll(std::initializer_list<T *> objects);
  template <class T>
  inline void deleteAll(std::vector<T *> &objects);
  inline bool isNumeric(const std::string &str);
  inline std::string stringLower(const std::string &in);
  inline std::vector<std::string> stringSplit(const std::string &str);
  inline std::vector<std::string> stringSplit(const std::string &str, const std::string &delim);
  inline std::string stringTrim(const std::string &str);

  // Checks a vector to see if any element of it equals a value.
  template <typename T>
  inline bool contains(const std::vector<T> &vec, const T &value)
  {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
  }

  /**
   * Calls the destructor on whatever object is pointed to, unless it's a
   * nullptr. Replaces the pointer with a nullptr.
   */
  template <class T>
  inline void deletePtr(T *&object)
  {
    if (object != nullptr)
    {
      delete object;
      object = nullptr;
    }
  }

  // Calls delete on all pointers passed (except nullptrs).
  template <class T>
  inline void deleteAll(std::initializer_list<T *> objects)
  {
    std::vector<T *> vec(objects.begin(), objects.end());
    deleteAll(vec);
  }

  // Calls delete on all pointers passed (except nullptrs).
  template <class T>
  inline void deleteAll(std::vector<T *> &objects)
  {
    for (size_t idx = 0; idx < objects.size(); idx++)
    {
      deletePtr(objects[idx]);
      objects[idx] = nullptr;
    }
  }

  // Returns true if the input is numeric. Does not ignore any whitespace.
  inline bool isNumeric(const std::string &str)
  {
    if (str.size() == 0)
    {
      return false;
    }

    size_t idx = 0;
    if (str[idx] == '+' || str[idx] == '-')
    {
      if (str.size() == 1)
      {
        return false;
      }
      idx++;
    }

    for (; idx < str.size(); idx++)
    {
      if (str[idx] < '0' || '9' < str[idx])
      {
        return false;
      }
    }

    return true;
  }

  // Returns a copy of the string with all letters converted to lowercase.
  inline std::string stringLower(const std::string &in)
  {
    std::string out = in;
    for (size_t idx = 0; idx < out.size(); idx++)
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
    size_t left = 0;
    size_t right = str.find(delim, left);
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
    const char _whitespace[] = {' ', '\n', '\t'};
    const auto WHITESPACE = std::vector<char>(_whitespace, _whitespace + 3);

    int start = 0;
    for (; (__SIZE_TYPE__)start < str.size(); start++)
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