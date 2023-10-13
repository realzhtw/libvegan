#include <vegan/file_input_port.h>
#include "platform/io.h"

namespace vegan {

  file_input_port::file_input_port(int fd, Long block_size, bool autoclose):
    fdport{fd, autoclose}, input_port{block_size} {}

  file_input_port::~file_input_port() {}

  Long file_input_port::backend_read_some(bytes_ref dst) { return platform::read_some(fd(), dst); }

}
