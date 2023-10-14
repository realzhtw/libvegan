#include <vegan/utf8.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(utf8, rune_length)
  {
    EXPECT_EQ(utf8::rune_length('a'), 1);
    EXPECT_EQ(utf8::rune_length(rune{418}), 2);
  }

}
