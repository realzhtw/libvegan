#include <vegan/file_output_port.h>
#include <vegan/io_error.h>
#include <vegan/stdio.h>
#include "platform/io.h"

namespace vegan {

  file_output_port::file_output_port(int fd, Long block_size, bool autoclose):
    fdport{fd, autoclose}, output_port{block_size} {}

  file_output_port::~file_output_port()
  {
    try { flush(); }
    catch (write_error &) {
      fprint(stderr, "could not flush output port buffer, some data is lost");
    }
  }

  void file_output_port::close()
  {
    flush();
    fdport::close();
  }

  Long file_output_port::backend_write_some(const_bytes_ref src) { return platform::write_some(fd(), src); }

}
