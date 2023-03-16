#include <vegan/file.h>
#include <vegan/io_error.h>
#include <vegan/platform/io.h>

namespace vegan {

  file::~file() { if (impl.autoclose && is_open()) close(); }

  Long file::get_block_size() { return platform::get_block_size(fd()); }

  void file::fdopen(int fd) { impl = Impl{fd, false}; }

  void file::write(const_bytes_ref b)
  {
    int n = platform::write(fd(), b.ptr(), b.size());
    if (n != b.size())
       throw write_error{};
  }

  void file::close() { platform::close(fd()); }

}
