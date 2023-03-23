#include <vegan/file_output_port.h>
#include <vegan/io_error.h>
#include <vegan/stdio.h>
#include <vegan/utils.h>

namespace vegan {

  file_output_port::file_output_port(int fd): file_port{fd}, buf{block_size()} {}

  file_output_port::~file_output_port()
  {
    try { flush(); }
    catch (write_error &) {
      fprint(stderr, "could not flush file buffer, some data is lost");
    }
  }

  void file_output_port::close()
  {
    flush();
    file_port::close();
  }

  void file_output_port::flush()
  {
    while (!buf.empty()) {
      auto r = f.write(buf.rd_ptr(), buf.bytes_left());
      if (r == 0) throw write_error{};
      buf.advance_rdpos(r);
    }
    buf.reset();
  }

  Long file_output_port::write_some(const byte *p, Long n)
  {
    if (buf.empty() && n > block_size())
      return f.write(p, block_size()); // write-through 

    auto k = min(n, buf.space_left());
    copy(buf.wr_ptr(), p, k);
    buf.advance_wrpos(k);

    if (buf.full()) flush();
    return k;
  }

  unbuffered_file_output_port::unbuffered_file_output_port(int fd): file_port{fd} {}
  unbuffered_file_output_port::~unbuffered_file_output_port() {}

  Long unbuffered_file_output_port::write_some(const byte *p, Long n) { return f.write(p, n); }
}
