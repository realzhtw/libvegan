#include <vegan/platform/alloc.h>

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

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

    Long write(int fd, const byte *p, Long n)
    {
      Long r;
      do {
        r = ::write(fd, p, n);
      } while (r == -1 && errno == EINTR);
      return r;
    }

  }
}
