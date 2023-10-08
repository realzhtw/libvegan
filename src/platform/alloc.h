#ifndef VEGAN_PLATFORM_ALLOC_H
#define VEGAN_PLATFORM_ALLOC_H

#include <vegan/types.h>

namespace vegan {
  namespace platform {

    void *alloc(Long);
    void free(void *);

  }
}

#endif
