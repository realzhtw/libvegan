#include <vegan/partition.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(partition, trivial)
  {
    EXPECT_EQ(partition({}, 0), 0);
    int x[] = {0};
    EXPECT_EQ(partition(x, -1), 0);
    EXPECT_EQ(partition(x, 0), 0);
    EXPECT_EQ(partition(x, 1), 1);
  }

  TEST(partition, two_1)
  {
    int x[] = { 3, 1 };
    EXPECT_EQ(partition(x, 1), 0);
  }

  TEST(partition, two_2)
  {
    int x[] = { 3, 1 };
    auto n = partition(x, 2);
    EXPECT_EQ(x[0], 1);
    EXPECT_EQ(x[1], 3);
    EXPECT_EQ(n, 1);
  }

  TEST(partition, two_3)
  {
    int x[] = { 3, 1 };
    auto n = partition(x, 3);
    EXPECT_EQ(x[0], 1);
    EXPECT_EQ(x[1], 3);
    EXPECT_EQ(n, 1);
  }

  TEST(partition, two_4)
  {
    int x[] = { 3, 1 };
    EXPECT_EQ(partition(x, 4), 2);
  }

}
