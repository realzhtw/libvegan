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

  TEST(string, find_char)
  {
    EXPECT_EQ(find("", 'x'), 0);
    EXPECT_EQ(find("x", 'x'), 0);
    EXPECT_EQ(find("x", 'y'), 1);
    EXPECT_EQ(find("xx", 'x'), 0);
    EXPECT_EQ(find("xy", 'y'), 1);
    EXPECT_EQ(find("xyz", 'y'), 1);
    EXPECT_EQ(find("Object-oriented programming offers a sustainable way to write spaghetti code.", 'o'), 7);
  }

  TEST(string, find_rune)
  {
    EXPECT_EQ(find("rune", rune{'e'}), 3);
    EXPECT_EQ(find("rune", rune{'x'}), 4);
    string s = u8"悖论\n";
    EXPECT_EQ(find(s, rune{0x6096}), 0);
    EXPECT_EQ(find(s, rune{0x6096}), 0);
    EXPECT_EQ(find(s, rune{0x8bba}), 3);
    EXPECT_EQ(find(s, rune{0x754c}), 7);
    EXPECT_EQ(find(s, rune{'\n'}), 6);
    EXPECT_EQ(find(s, rune{'x'}), 7);
  }

  //TEST(string, split)
  //{
  //  auto v = split("root:x:0:0:root:/root:/bin/ksh", ':');
  //  EXPECT_EQ(v.size(), 7);
  //  EXPECT_EQ(v[0], "root"
  //}

}
