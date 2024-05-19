#include <vector>

#include "lib/catch.hpp"

#include "src/Card.hpp"
#include "src/Util.hpp"

TEST_CASE("contains", "[Util]")
{
  char _letters[] = "abcde";
  auto letters = std::vector<char>(_letters, _letters + 5);
  CHECK(Util::contains<char>(letters, 'c'));
  CHECK(!Util::contains<char>(letters, 'f'));

  std::string _words[] = {"alpha", "beta", "gamma", "delta", "epsilon"};
  auto words = std::vector<std::string>(_words, _words + 5);
  CHECK(Util::contains<std::string>(words, "gamma"));
  CHECK(!Util::contains<std::string>(words, "zeta"));

  int _numbers[] = {1, 2, 3, 4, 5};
  auto numbers = std::vector<int>(_numbers, _numbers + 5);
  CHECK(Util::contains<int>(numbers, 3));
  CHECK(!Util::contains<int>(numbers, 6));
}

TEST_CASE("deletePtr updates ptr to nullptr", "[Util::deletePtr]")
{
  /*
   *Testing for actual deletion is not an easy task, so it fall outside of this
   * scope.
   */
  Card *ptr = new Card("QH");
  Util::deletePtr(ptr);
  CHECK(ptr == nullptr);
}

TEST_CASE("accurately identify numeric strings", "[Util::isNumeric]")
{
  std::string str0 = "";
  std::string str1 = " ";
  std::string str2 = "+";
  std::string str3 = "-";
  std::string str4 = "-test";
  std::string str5 = "+test";
  std::string str6 = "test";
  std::string str7 = "123";
  std::string str8 = " 123";
  std::string str9 = "-123";
  std::string str10 = "+123";

  CHECK(Util::isNumeric(str0) == false);
  CHECK(Util::isNumeric(str1) == false);
  CHECK(Util::isNumeric(str2) == false);
  CHECK(Util::isNumeric(str3) == false);
  CHECK(Util::isNumeric(str4) == false);
  CHECK(Util::isNumeric(str5) == false);
  CHECK(Util::isNumeric(str6) == false);
  CHECK(Util::isNumeric(str7) == true);
  CHECK(Util::isNumeric(str8) == false);
  CHECK(Util::isNumeric(str9) == true);
  CHECK(Util::isNumeric(str10) == true);
}

TEST_CASE("convert string to lowercase", "[Util::stringLower]")
{
  std::string word = "WoRd";
  CHECK(Util::stringLower(word) == "word");
}

TEST_CASE("splits strings", "[Util::stringSplit]")
{
  std::string list = "Alpha,Beta,Gamma,Delta,Epsilon";
  std::vector<std::string> expected1;
  expected1.push_back("Alpha");
  expected1.push_back("Beta");
  expected1.push_back("Gamma");
  expected1.push_back("Delta");
  expected1.push_back("Epsilon");
  auto actual1 = Util::stringSplit(list);
  CHECK(expected1 == actual1);

  std::string phrase = "Lorem ipsum dolor sit amet";
  std::vector<std::string> expected2;
  expected2.push_back("Lorem");
  expected2.push_back("ipsum");
  expected2.push_back("dolor");
  expected2.push_back("sit");
  expected2.push_back("amet");
  auto actual2 = Util::stringSplit(phrase, " ");
  CHECK(expected2 == actual2);

  std::string numbers = "one, two, three, four, five";
  std::vector<std::string> expected3;
  expected3.push_back("one");
  expected3.push_back("two");
  expected3.push_back("three");
  expected3.push_back("four");
  expected3.push_back("five");
  auto actual3 = Util::stringSplit(numbers, ", ");
  CHECK(expected3 == actual3);

  std::string empties = ",hello,,world,";
  std::vector<std::string> expected4;
  expected4.push_back("");
  expected4.push_back("hello");
  expected4.push_back("");
  expected4.push_back("world");
  expected4.push_back("");
  auto actual4 = Util::stringSplit(empties);
  CHECK(expected4 == actual4);
}

TEST_CASE("trims whitespace from strings", "[Util::stringTrim]")
{
  std::string whitespaceWord = " \n\tword\t\n ";
  std::string phrase = "middle space";
  std::string spaces = "          ";
  std::string space = " ";
  std::string empty = "";

  CHECK(Util::stringTrim(whitespaceWord) == "word");
  CHECK(Util::stringTrim(phrase) == "middle space");
  CHECK(Util::stringTrim(spaces) == "");
  CHECK(Util::stringTrim(space) == "");
  CHECK(Util::stringTrim(empty) == "");
}