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
      auto r = f.write({buf.rd_ptr(), buf.bytes_left()});
      if (r == 0) throw write_error{};
      buf.advance_rdpos(r);
    }
    buf.reset();
  }

  Long file_output_port::write_some(const_bytes_ref b)
  {
    if (buf.empty() && b.size() > block_size())
      return f.write(first_n(b, block_size())); // avoid buffer

    auto n = min(b.size(), buf.space_left());
    copy(buf.wr_ptr(), first_n(b, n));
    buf.advance_wrpos(n);

    if (buf.full()) flush();
    return n;
  }

  unbuffered_file_output_port::unbuffered_file_output_port(int fd): file_port{fd} {}
  unbuffered_file_output_port::~unbuffered_file_output_port() {}

  Long unbuffered_file_output_port::write_some(const_bytes_ref b) { return f.write(b); }
}
