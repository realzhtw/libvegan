#include <vegan/output_buffer.h>
#include <vegan/string_ref.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(output_buffer, default_constructor)
  {
    output_buffer obuf;
    EXPECT_EQ(obuf.size(), 0);
    EXPECT_TRUE(obuf.empty());
    EXPECT_TRUE(obuf.full());
  }

  TEST(output_buffer, one_byte)
  {
    output_buffer obuf{1};
    EXPECT_EQ(obuf.size(), 1);
    EXPECT_TRUE(obuf.empty());
    EXPECT_FALSE(obuf.full());
    string_ref s = "xxx";
    auto n = obuf.write_some(s.as_bytes());
    EXPECT_EQ(n, 1);
    EXPECT_EQ(obuf.data(), first_n(s.as_bytes(), 1));
    EXPECT_FALSE(obuf.empty());
    EXPECT_TRUE(obuf.full());
    EXPECT_EQ(obuf.space_left(), 0);
    obuf.reset();
    EXPECT_EQ(obuf.size(), 1);
    EXPECT_TRUE(obuf.empty());
    EXPECT_FALSE(obuf.full());
    EXPECT_EQ(obuf.space_left(), obuf.size());
  }

}
