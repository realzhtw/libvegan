#include <vegan/utils.h>
#include <vegan/string.h>

namespace vegan {

  string to_string(int x)
  {
    char buf[21];
    buf[20] = '0' + abs(x % 10);
    bool neg = x < 0;
    x /= 10;
    x = abs(x);
    int i = 19;
    while (x > 0) {
      buf[i--] = '0' + x % 10;
      x /= 10;
    }
    if (neg) buf[i--] = '-';
    ++i;
    int n = 21 - i;
    return string{buf+i, n};
  }

}
