#ifndef VEGAN_PLATFORM_IO_H
#define VEGAN_PLATFORM_IO_H

#include <vegan/types.h>
#include <vegan/bytes_ref.h>

namespace vegan {
  namespace platform {

    int open(const char *path, int flags);
    bool close(int);

    Long get_block_size(int fd);

    Long read(int fd, byte *buf, Long n);

    void write(int fd, const_bytes_ref);
    Long write_some(int fd, const_bytes_ref);

  }
}

#endif
