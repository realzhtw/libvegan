#include <vegan/file_input_port.h>
#include <vegan/utils.h>

namespace vegan {

  file_input_port::file_input_port(int fd, int lookahead): file_port{fd}, buf{block_size()+lookahead} {}

  file_input_port::~file_input_port() {}

  Long file_input_port::read_some(bytes_ref b)
  {
    if (empty(b)) return 0;

    if (buf.empty()) {
      buf.reset();

      if (b.size() > block_size())
        return f.read(first_n(b, block_size())); // avoid buffer

      auto r = f.read({buf.wr_ptr(), buf.space_left()});
      buf.advance_wrpos(r);
    }

    auto r = min(b.size(), buf.bytes_left());
    copy(b.ptr(), buf.rd_ptr(), r);
    buf.advance_rdpos(r);
    return r;
  }

  bool file_input_port::unread(const byte *p, Long n)
  {
    if (buf.rd_pos() < n) return false;
    copy(buf.rd_ptr() - n, p, n);
    buf.back_off(n);
    return true;
  }

}
