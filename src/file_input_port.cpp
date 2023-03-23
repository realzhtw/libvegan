#include <vegan/file_input_port.h>
#include <vegan/utils.h>

namespace vegan {

  file_input_port::file_input_port(int fd, int lookahead): file_port{fd}, buf{block_size()+lookahead} {}

  file_input_port::~file_input_port() {}

  Long file_input_port::read_some(byte *p, Long n)
  {
    if (n == 0) return 0;

    if (buf.empty()) {
      buf.reset();

      if (n > block_size())
        return f.read(p, block_size()); // read-through

      auto r = f.read(buf.wr_ptr(), buf.space_left());
      buf.advance_wrpos(r);
    }

    auto r = min(n, buf.bytes_left());
    copy(p, buf.rd_ptr(), r);
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
