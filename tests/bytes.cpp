#include <vegan/bytes.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(bytes, simple)
  {
    bytes b;
    EXPECT_EQ(b.size(), 0);
    b = bytes{10, 244};
    EXPECT_EQ(b.size(), 10);
    EXPECT_EQ(b[9], 244);
  }

}
