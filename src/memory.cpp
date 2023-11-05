#include <vegan/memory.h>

#include <cstdlib>

namespace vegan {

  void *alloc(Long n, Long alignment)
  {
    if (alignment < 2 * sizeof(void *))
      return malloc(n);
    void *p = nullptr;
    ::posix_memalign(&p, alignment, n);
    return p;
  }

  void free(void *p) { ::free(p); }

}
