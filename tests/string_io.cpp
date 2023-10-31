#include <vegan/string_io.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(string_io, parse_rune)
  {
    string_ref input;
    rune r;
    EXPECT_FALSE(parse_rune(input, r));
    EXPECT_TRUE(input.empty());
    input = "o";
    EXPECT_TRUE(parse_rune(input, r));
    EXPECT_TRUE(input.empty());
  }

}
