#include <vegan/string_output_port.h>
#include <vegan/stdio.h>
#include <vegan/string.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(string, simple)
  {
    string s;
    EXPECT_EQ(s.size(), 0);
    s = "love";
    EXPECT_EQ(s.size(), 4);
    s = "all you need is " + s;
    EXPECT_EQ(s.size(), 20);
  }

  TEST(string, has_prefix)
  {
    EXPECT_TRUE(has_prefix("", ""));
    EXPECT_FALSE(has_prefix("", "x"));
    EXPECT_TRUE(has_prefix("x", "x"));
    EXPECT_TRUE(has_prefix("xy", "x"));
    EXPECT_FALSE(has_prefix("x", "y"));
    EXPECT_FALSE(has_prefix("x", "xy"));
    EXPECT_TRUE(has_prefix("Object-oriented design is the roman numerals of computing.", "Ob"));
  }

  TEST(string, has_suffix)
  {
    EXPECT_TRUE(has_suffix("", ""));
    EXPECT_FALSE(has_suffix("", "x"));
    EXPECT_TRUE(has_suffix("x", "x"));
    EXPECT_TRUE(has_suffix("yx", "x"));
    EXPECT_FALSE(has_suffix("x", "y"));
    EXPECT_FALSE(has_suffix("x", "yx"));
    EXPECT_TRUE(has_suffix("Object-oriented design is the roman numerals of computing.", "g."));
  }

}
