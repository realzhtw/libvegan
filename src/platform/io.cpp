#include "io.h"

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

#include <vegan/io_error.h>

namespace vegan {
  namespace platform {

    bool close(int fd) { return ::close(fd) == 0; }

    Long get_block_size(int fd)
    {
      struct stat buf;
      fstat(fd, &buf);
      return buf.st_blksize;
    }

    Long read_some(int fd, bytes_ref b)
    {
      Long r;
      do  {
        r = ::read(fd, b.ptr(), b.size());
      } while (r == -1 && errno == EINTR);
      if (r == -1)
        throw read_error{};
      return r;
    }

    Long write_some(int fd, const_bytes_ref b)
    {
      Long r;
      do {
        r = ::write(fd, b.ptr(), b.size());
      } while (r == -1 && errno == EINTR);
      if (r == -1)
        throw write_error{};
      return r;
    }
  }
}
