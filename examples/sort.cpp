#include <vegan/vector.h>
#include <vegan/sort.h>
#include <vegan/bsearch.h>
#include <vegan/stdio.h>

using namespace vegan;

int main()
{
  vector<int> x{10};

  x[0] = 1;
  x[1] = -42026;
  x[2] = 5;
  x[3] = 4;
  x[4] = -3;
  x[5] = 2;
  x[6] = 9;
  x[7] = 10;
  x[8] = 248;
  x[9] = 7;

  println("Original: ", x);

  sort(x);

  println("Sorted: ", x);

  for (int i = 0; i != 9; ++i) {
    if (!(x[i] < x[i+1]))
      return i;
  }

  for (int i = 0; i != 9; ++i) {
    auto pos = bsearch(x, x[i]);
    println("bsearch(", x, ", ", x[i], ") = ", pos);
  }

  return 0;
}
