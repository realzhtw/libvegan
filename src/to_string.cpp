#include <vegan/utils.h>
#include <vegan/string.h>
#include <vegan/string_buf.h>

namespace {
  using namespace vegan;

  template<typename T> string signed_integer_to_string(T x)
  {
    constexpr int n = sizeof(x)*10/4+1;
    char buf[n];
    buf[n-1] = '0' + abs(x % 10);
    bool neg = x < 0;
    x /= 10;
    x = abs(x);
    int i = n-2;
    while (x > 0) {
      buf[i--] = '0' + x % 10;
      x /= 10;
    }
    if (neg) buf[i--] = '-';
    ++i;
    return string{buf+i, n-i};
   }

}

namespace vegan {
  
  string to_string(short x) { return signed_integer_to_string(x); }
  string to_string(int x) { return signed_integer_to_string(x); }
  string to_string(long x) { return signed_integer_to_string(x); }
  string to_string(long long x) { return signed_integer_to_string(x); }

}
