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

}
