#include <vegan/span.h>
#include <vegan/utils.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(sorted, trivial)
  {
    EXPECT_TRUE(sorted<int>(span<int>{}));
    int x[] = {-422};
    EXPECT_TRUE(sorted(x));
  }

  TEST(sorted, two)
  {
    int x[] = { 1, 0 };
    EXPECT_FALSE(sorted(x));
    swap(x[0], x[1]);
    EXPECT_TRUE(sorted(x));
    x[1] = 0;
    EXPECT_TRUE(sorted(x));
  }

  TEST(sorted, ten)
  {
    int x[] = { -1, 0, 1, 42, 244, 4 };
    EXPECT_FALSE(sorted(x));
    swap(x[4], x[5]);
    swap(x[3], x[4]);
    EXPECT_TRUE(sorted(x));
  }

}
