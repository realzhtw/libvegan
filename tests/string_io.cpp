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
    input = u8"oÀͽ";
    EXPECT_TRUE(parse_rune(input, r));
    EXPECT_EQ(ord(r), 'o');
    EXPECT_TRUE(parse_rune(input, r));
    EXPECT_EQ(ord(r), 0xc0);
    EXPECT_TRUE(parse_rune(input, r));
    EXPECT_EQ(ord(r), 0x37d);
    EXPECT_TRUE(input.empty());
    input = u8":AZazÀÖ";
    parse_rune(input, r);
    parse_rune(input, r);
    parse_rune(input, r);
    parse_rune(input, r);
    parse_rune(input, r);
    parse_rune(input, r);
    EXPECT_EQ(ord(r), 0xc0);
  }

}
