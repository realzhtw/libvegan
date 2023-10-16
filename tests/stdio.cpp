#include <vegan/stdio.h>
#include <vegan/string_output_port.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(stdio, fwrite)
  {
    string_output_port s;
    fprint(s, 'x');
    EXPECT_EQ(s.data().size(), 1);
    fprint(s, rune{418});
    EXPECT_EQ(s.data().size(), 3);
  }

}
