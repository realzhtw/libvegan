#include <vegan/file_output_port.h>
#include <vegan/io_error.h>
#include <vegan/stdio.h>
#include <vegan/utils.h>

#include "platform/io.h"

namespace vegan {

  file_output_port::file_output_port(int fd, Long buffer_size, bool autoclose):
    fdport{fd, autoclose}, buf{buffer_size} {}

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
    fdport::close();
  }

  void file_output_port::flush()
  {
    platform::write(fd(), first_n(buf, buf_wrpos));
    buf_wrpos = 0;
  }

  Long file_output_port::write_some(const_bytes_ref b)
  {
    if (buf_wrpos == 0 && b.size() > buf.size())
      return platform::write_some(fd(), first_n(b, buf.size())); // avoid buffer

    auto n = min(b.size(), buf.size() - buf_wrpos);
    copy(buf.ptr(buf_wrpos), first_n(b, n));
    buf_wrpos += n;

    if (buf_wrpos == buf.size()) flush();
    return n;
  }

}
