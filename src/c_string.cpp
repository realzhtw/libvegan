#include <vegan/c_string.h>

namespace vegan {

  Long c_string_length(const char *s)
  {
    Long n = 0;
    while (*s++) ++n;
    return n;
  }

  Long c_string_copy(bytes_ref dst, const char *s)
  {
    Long i = 0;
    Long maxlen = dst.size() - 1;
    while (i < maxlen && *s)
      dst[i++] = *s++;
    dst[i] = 0;
    return i;
  }

}
