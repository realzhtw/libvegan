#include <vegan/platform/alloc.h>

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

namespace vegan {
  namespace platform {

    void *alloc(long n) { return ::malloc(n); }
    void free(void *p) { ::free(p); }

    bool close(int fd) { return ::close(fd) == 0; }

    Long get_block_size(int fd)
    {
      struct stat buf;
      fstat(fd, &buf);
      return buf.st_blksize;
    }

    Long write(int fd, const Byte *p, Long n)
    {
      int r = 0;
      do {
        r = ::write(fd, p, n);
      } while (r == -1 && errno == EINTR);
      return r;
    }

  }
}
