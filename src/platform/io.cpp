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

    Long read(int fd, byte *p, Long n)
    {
      Long r;
      do  {
        r = ::read(fd, p, n);
      } while (r == -1 && errno == EINTR);
      return r;
    }

    Long write_some(int fd, const_bytes_ref b)
    {
      Long r;
      do {
        r = ::write(fd, b.ptr(), b.size());
      } while (r == -1 && errno == EINTR);
      return r;
    }

    void write(int fd, const_bytes_ref b)
    {
      while (b.size() != 0) {
        auto n = platform::write_some(fd, b);
        if (n == -1)
          throw write_error{};
        b.drop_first(n);
      }
    }

  }
}
