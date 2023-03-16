#include <vegan/c_string.h>

namespace vegan {

  Long c_string_length(const char *s)
  {
    Long n = 0;
    while (*s++) ++n;
    return n;
  }

}
