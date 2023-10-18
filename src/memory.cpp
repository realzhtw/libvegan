#include <vegan/memory.h>

#include <cstdlib>

namespace vegan {

  void *alloc(Long n, Long alignment)
  {
    return ::aligned_alloc(alignment, n);
  }

  void free(void *p) { ::free(p); }

}
