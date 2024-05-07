#include <vector>

#include "lib/catch.hpp"

#include "src/Util.hpp"

TEST_CASE("contains")
{
  char _letters[] = "abcde";
  auto letters = std::vector<char>(_letters, _letters + 5);
  REQUIRE(Util::contains<char>(letters, 'c'));
  REQUIRE(!Util::contains<char>(letters, 'f'));

  std::string _words[] = {"alpha", "beta", "gamma", "delta", "epsilon"};
  auto words = std::vector<std::string>(_words, _words + 5);
  REQUIRE(Util::contains<std::string>(words, "gamma"));
  REQUIRE(!Util::contains<std::string>(words, "zeta"));

  int _numbers[] = {1, 2, 3, 4, 5};
  auto numbers = std::vector<int>(_numbers, _numbers + 5);
  REQUIRE(Util::contains<int>(numbers, 3));
  REQUIRE(!Util::contains<int>(numbers, 6));
}