#include <vegan/file_output_port.h>

namespace vegan {

  file_output_port::file_output_port(int fd)
  {
    f.fdopen(fd);
    output_buf.resize(f.get_block_size());
  }

  file_output_port::~file_output_port() { flush(); }

  void file_output_port::close()
  {
    flush();
    file_port::close();
  }

  void file_output_port::flush()
  {
    if (!output_buf.empty()) {
      f.write(output_buf.data());
      output_buf.reset();
    }
  }

  void file_output_port::write(const_bytes_ref b)
  {
    while (!b.empty()) {
      auto n = output_buf.write(b);
      if (output_buf.full())
        flush();
      b.drop_first(n);
    }
  }

}
