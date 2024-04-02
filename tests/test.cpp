#include <catch2/catch_test_macros.hpp>

#include "vis.h"

#include <sstream>
#include <any>

TEST_CASE( "prn with cout", "[prn_cout]" ) {
  cppvis::prn(std::tuple( 1, 'a', false ));
}

TEST_CASE( "pr with float vector", "[pr_float_vector]" ) {
  std::ostringstream s;
  cppvis::pr(s, std::vector<float>{ 1.0f, 2.0f, 3.0f });
  REQUIRE(s.str() == "[ 1 2 3 ]");
}

TEST_CASE( "pr with char vector", "[pr_char_vector]" ) {
  std::ostringstream s;
  cppvis::pr(s, std::vector<char>{ 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd' });
  REQUIRE(s.str() == "[ \\H \\e \\l \\l \\o \\space \\W \\o \\r \\l \\d ]");
}

TEST_CASE( "pr with heterogeneous vector", "[pr_heterogeneous_vector]" ) {
  std::ostringstream s;
  cppvis::pr(s, std::vector<std::any>{ 'a', 10.1, false });
  REQUIRE(s.str() == "[ \\a 10.1 false ]");
}

TEST_CASE( "pr with string", "[pr_string]" ) {
  std::ostringstream s;
  cppvis::pr(s, std::string("Hello world!"));
  REQUIRE(s.str() == "\"Hello world!\"");
}

TEST_CASE( "pr with map", "[pr_map]" ) {
  std::map<std::string, int> M;
  M.insert_or_assign("key1", 1);
  M.insert_or_assign("key2", 2);

  std::ostringstream s;
  cppvis::pr(s, M);
  REQUIRE(s.str() == "{ \"key1\" 1, \"key2\" 2 }");
}

TEST_CASE( "pr with pair", "[pr_pair]" ) {
  std::ostringstream s;
  cppvis::pr(s, std::pair(' ', -10.1f));
  REQUIRE(s.str() == "[ \\space -10.1 ]");
}

TEST_CASE( "pr with tuple", "[pr_tuple]" ) {
  std::ostringstream s;
  cppvis::pr(s, std::tuple('a', 10.1, false));
  REQUIRE(s.str() == "[ \\a 10.1 false ]");
}
