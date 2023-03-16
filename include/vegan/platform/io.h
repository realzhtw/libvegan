#ifndef VEGAN_PLATFORM_IO_H
#define VEGAN_PLATFORM_IO_H

#include <vegan/types.h>

namespace vegan {
  namespace platform {

    int open(const char *path, int flags);
    bool close(int);

    Long get_block_size(int fd);

    Long read(int fd, Byte *buf, Long n);
    Long write(int fd, const Byte *buf, Long n);

  }
}

#endif
