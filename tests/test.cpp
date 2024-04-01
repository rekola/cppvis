#include <catch2/catch_test_macros.hpp>

#include "vis.h"

#include <sstream>

TEST_CASE( "pr with float vector", "[pr_float_vector]" ) {
  std::ostringstream s;
  cppvis::pr(s, std::vector<float>{ 1.0f, 2.0f, 3.0f});
  REQUIRE(s.str() == "[ 1 2 3 ]");
}

TEST_CASE( "pr with string", "[pr_string]" ) {
  std::ostringstream s;
  cppvis::pr(s, std::string("Hello world!"));
  REQUIRE(s.str() == "\"Hello world!\"");
}
