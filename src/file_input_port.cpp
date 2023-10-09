#include <vegan/file_input_port.h>
#include <vegan/utils.h>

#include "platform/io.h"

namespace {
  using namespace vegan;

  Long read_at_least(int fd, bytes_ref buf, Long n)
  {
    Long bytes_read = 0;
    while (bytes_read < n) {
      auto r = platform::read_some(fd, buf);
      if (r == 0)
        break;
      bytes_read += r;
    }
    return bytes_read;
  }
}

namespace vegan {

  const auto utf8_lookahead = 6;

  file_input_port::file_input_port(int fd, bool buffered, bool autoclose):
    fdport{fd, autoclose}
  {
    if (buffered) {
      block_size = platform::get_block_size(fd);
      buf = bytes{block_size + utf8_lookahead};
    }
  }

  file_input_port::~file_input_port() {}

  Long file_input_port::peak(bytes_ref b)
  {
    if (b.size() == 0) return 0;

    b.crop(utf8_lookahead);

    auto bytes_left = buf_end - buf_rdpos;
    if (bytes_left < b.size()) {
      copy(buf.ptr(), buf.ptr(buf_rdpos), bytes_left);
      buf_rdpos = 0;
      buf_end = bytes_left;
      buf_end += read_at_least(fd, bytes_ref{buf.ptr(buf_end), buf.size() - buf_end});
    }

    auto r = min(b.size(), buf_end - buf_rdpos);
    copy(b.ptr(), buf.ptr(buf_rdpos), r);

    return r;
  }

  Long file_input_port::read_some(bytes_ref b)
  {
    if (b.size() == 0) return 0;



      if (b.size() > buf.size())
        return platform::read_some(fd(), first_n(b, block_size)); // avoid buffer

      buf_end = platform::read_some(fd(), {buf.ptr(), block_size});
    }

    auto r = min(b.size(), buf_end - buf_rdpos);
    copy(b.ptr(), buf.ptr(buf_rdpos), r);
    buf_rdpos += r;
    return r;
  }

  bool file_input_port::unread(const_bytes_ref b)
  {
    if (buf_end < b.size()) return false;
    copy(buf.rd_ptr() - b.size(), b);
    buf.back_off(b.size());
    return true;
  }

}
