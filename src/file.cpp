#include <vegan/file.h>
#include <vegan/io_error.h>
#include "platform/io.h"

namespace vegan {

  file::~file() { if (impl.autoclose && is_open()) close(); }

  Long file::get_block_size() { return platform::get_block_size(fd()); }

  void file::fdopen(int fd) { impl = Impl{fd, false}; }

  Long file::write(const_bytes_ref b)
  {
    auto r = platform::write_some(fd(), b);
    if (r == -1)
       throw write_error{};
    return r;
  }

  //void file::write(const_bytes_ref b) { return write(b.ptr(), b.size()); }

  Long file::read(bytes_ref b)
  {
    auto r = platform::read(fd(), b.ptr(), b.size());
    if (r == -1)
      throw read_error{};
    return r;
  }

  //Long file::read(bytes_ref b) { return read(b.ptr(), b.size()); }

  void file::close() { platform::close(fd()); }

}
