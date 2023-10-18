#include <vegan/bytes.h>
#include <vegan/memory.h>
#include <vegan/vector_ref.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  struct T {
    T() {}
    T(T &&t): x{t.x} { t.x = -1; }
    ~T() { x = 0; }
    int x = 1;
  };

  TEST(initialize, simple)
  {
    bytes b{10 * (Long)sizeof(T)};
    auto ten = b.as_vector<T>();
    auto first_five = first_n(ten, 5);
    auto last_five = last_n(ten, 5);
    initialize(first_five);
    for (Long i = 0; i < 5; ++i)
      EXPECT_EQ(first_five[i].x, 1);
    initialize(last_five, move(first_five));
    for (Long i = 0; i < 5; ++i)
      EXPECT_EQ(last_five[i].x, 1);
    for (Long i = 0; i < 5; ++i)
      EXPECT_EQ(first_five[i].x, -1);
    destroy(ten);
    for (Long i = 0; i < 10; ++i)
      EXPECT_EQ(first_five[i].x, 0);
  }

}
