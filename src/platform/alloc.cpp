#include "alloc.h"

#include <stdlib.h>

namespace vegan {
  namespace platform {

    void *alloc(long n) { return ::malloc(n); }
    void free(void *p) { ::free(p); }

  }
}
