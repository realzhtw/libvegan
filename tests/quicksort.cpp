#include <vegan/quicksort.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(quicksort, trivial)
  {
    int x[] = {-422};
    quicksort(x);
    EXPECT_EQ(x[0], -422);
  }

  TEST(quicksort, two_1)
  {
    int x[] = { 0, 1 };
    quicksort(x);
    EXPECT_EQ(x[0], 0);
    EXPECT_EQ(x[1], 1);
  }

  TEST(quicksort, two_2)
  {
    int x[] = { 1, 0 };
    quicksort(x);
    EXPECT_EQ(x[0], 0);
    EXPECT_EQ(x[1], 1);
  }

  TEST(quicksort, ten)
  {
    int x[] = { -4, 42, 12, 13, -5, 2, 2, 0 };
    quicksort(x);
    EXPECT_TRUE(sorted(x));
  }

}
