#include <vegan/file.h>
#include <vegan/io_error.h>
#include <vegan/platform/io.h>

namespace vegan {

  file::~file() { if (impl.autoclose && is_open()) close(); }

  Long file::get_block_size() { return platform::get_block_size(fd()); }

  void file::fdopen(int fd) { impl = Impl{fd, false}; }

  void file::write(const byte *p, Long n)
  {
    auto r = platform::write(fd(), p, n);
    if (r != n)
       throw write_error{};
  }

  void file::write(const_bytes_ref b) { return write(b.ptr(), b.size()); }

  Long file::read(byte *p, Long n)
  {
    auto r = platform::read(fd(), p, n);
    if (r == -1)
      throw read_error{};
    return r;
  }

  Long file::read(bytes_ref b) { return read(b.ptr(), b.size()); }

  void file::close() { platform::close(fd()); }

}
