#include <vegan/holder_ptr.h>
#include <vegan/unique_ptr.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  struct X {
    X(int &x): p{&x} {}
    ~X() { *p = 0; }
    int *p;
  };

  TEST(holder_ptr, default_constructor)
  {
    holder_ptr<int> p;
    EXPECT_FALSE(p.owns());
    EXPECT_EQ(p.get(), nullptr);
  }


  TEST(holder_ptr, not_owner)
  {
    int g = 10;
    auto u = make_unique<X>(g);
    {
      holder_ptr<X> h{u.get()};
      EXPECT_EQ(g, 10);
      EXPECT_FALSE(h.owns());
    }
    EXPECT_EQ(g, 10);
  }

  TEST(holder_ptr, owner)
  {
    int g = 10;
    auto u = make_unique<X>(g);
    {
      holder_ptr<X> h = move(u);
      EXPECT_EQ(g, 10);
      EXPECT_TRUE(h.owns());
    }
    EXPECT_EQ(g, 0);
  }

}
