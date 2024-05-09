#include <vector>

#include "lib/catch.hpp"

#include "src/Util.hpp"

TEST_CASE("contains", "[Util]")
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

TEST_CASE("stringLower", "[Util]")
{
  std::string word = "WoRd";
  REQUIRE(Util::stringLower(word) == "word");
}

TEST_CASE("stringSplit", "[Util]")
{
  std::string list = "Alpha,Beta,Gamma,Delta,Epsilon";
  std::vector<std::string> expected1;
  expected1.push_back("Alpha");
  expected1.push_back("Beta");
  expected1.push_back("Gamma");
  expected1.push_back("Delta");
  expected1.push_back("Epsilon");
  auto actual1 = Util::stringSplit(list);
  REQUIRE(expected1 == actual1);

  std::string phrase = "Lorem ipsum dolor sit amet";
  std::vector<std::string> expected2;
  expected2.push_back("Lorem");
  expected2.push_back("ipsum");
  expected2.push_back("dolor");
  expected2.push_back("sit");
  expected2.push_back("amet");
  auto actual2 = Util::stringSplit(phrase, " ");
  REQUIRE(expected2 == actual2);

  std::string numbers = "one, two, three, four, five";
  std::vector<std::string> expected3;
  expected3.push_back("one");
  expected3.push_back("two");
  expected3.push_back("three");
  expected3.push_back("four");
  expected3.push_back("five");
  auto actual3 = Util::stringSplit(numbers, ", ");
  REQUIRE(expected3 == actual3);

  std::string empties = ",hello,,world,";
  std::vector<std::string> expected4;
  expected4.push_back("");
  expected4.push_back("hello");
  expected4.push_back("");
  expected4.push_back("world");
  expected4.push_back("");
  auto actual4 = Util::stringSplit(empties);
  REQUIRE(expected4 == actual4);
}

TEST_CASE("stringTrim", "[Util]")
{
  std::string whitespaceWord = " \n\tword\t\n ";
  REQUIRE(Util::stringTrim(whitespaceWord) == "word");

  std::string phrase = "middle space";
  REQUIRE(Util::stringTrim(phrase) == "middle space");
}