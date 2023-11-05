#include <vegan/bytes_ref.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(bytes_ref, simple)
  {
    byte buf[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    bytes_ref b{buf};
    EXPECT_EQ(b.size(), 10);
    EXPECT_EQ(b[9], 9);
    b.drop_first();
    EXPECT_EQ(b.size(), 9);
    EXPECT_EQ(b[0], 1);
    b.drop_last();
    EXPECT_EQ(b.size(), 8);
    EXPECT_EQ(b[b.size()-1], 8);
    b.drop_first(100);
    EXPECT_EQ(b.size(), 0);
    b.drop_last(100);
    EXPECT_EQ(b.size(), 0);
  }

}
