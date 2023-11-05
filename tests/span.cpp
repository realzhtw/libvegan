#include <vegan/span.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(span, simple)
  {
    int buf[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto s = as_span(buf);
    EXPECT_EQ(s.size(), 10);
    EXPECT_EQ(s[9], 9);
    EXPECT_EQ(drop_first(s, 3).size(), 7);
    EXPECT_EQ(drop_first(s, 3).front(), 3);
    EXPECT_EQ(drop_first(s, 3).back(), 9);
    EXPECT_EQ(drop_first(s, 100).size(), 0);
    EXPECT_EQ(drop_last(s, 3).size(), 7);
    EXPECT_EQ(drop_last(s, 100).size(), 0);
    EXPECT_EQ(drop_last(s, 3).front(), 0);
    EXPECT_EQ(drop_last(s, 3).back(), 6);
    EXPECT_EQ(first_n(s, 5).size(), 5);
    EXPECT_EQ(first_n(s, 5).front(), 0);
    EXPECT_EQ(first_n(s, 5).back(), 4);
    EXPECT_EQ(first_n(s, 100).size(), 10);
    EXPECT_EQ(first_n(s, 100).back(), 9);
    EXPECT_EQ(last_n(s, 5).size(), 5);
    EXPECT_EQ(last_n(s, 5).front(), 5);
    EXPECT_EQ(last_n(s, 5).back(), 9);
    EXPECT_EQ(last_n(s, 100).size(), 10);
    EXPECT_EQ(last_n(s, 100).back(), 9);
    EXPECT_EQ(cut(s, 2, 6).size(), 6);
    EXPECT_EQ(cut(s, 2, 6).front(), 2);
    EXPECT_EQ(cut(s, 2, 6).back(), 7);
    EXPECT_EQ(cut(s, 100, 10).size(), 0);
    EXPECT_EQ(cut(s, 0, 100).size(), 10);
    s.drop_first();
    EXPECT_EQ(s.size(), 9);
    EXPECT_EQ(s.front(), 1);
    s.drop_last();
    EXPECT_EQ(s.size(), 8);
    EXPECT_EQ(s.back(), 8);
    s.drop_first(100);
    EXPECT_EQ(s.size(), 0);
    s.drop_last(100);
    EXPECT_EQ(s.size(), 0);
  }

  TEST(span, covertion)
  {
    int a[] = { 0, 1, 2 };
    const int ca[] = { 0, 1 };
    auto s = as_span(a);
    auto cs = as_span(ca);
    cs = s;
    EXPECT_EQ(cs.size(), 3);
  }

}
