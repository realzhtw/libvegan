#include <vegan/unique_ptr.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  int g = 10;

  struct X { ~X() { g = 0; } };

  TEST(unique_ptr, simple)
  {
    unique_ptr<X> p;
    EXPECT_EQ(p.get(), nullptr);

    p = make_unique<X>();
    EXPECT_EQ(g, 10);
    p.reset();
    EXPECT_EQ(g, 0);
  }

}
