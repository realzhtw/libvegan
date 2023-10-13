#ifndef VEGAN_FILE_INPUT_PORT_H
#define VEGAN_FILE_INPUT_PORT_H

#include <vegan/bytes.h>
#include <vegan/input_port.h>
#include <vegan/fdport.h>

namespace vegan {

  class file_input_port: public fdport, public input_port {
    public:
      file_input_port() {}
      explicit file_input_port(int fd, Long block_size, bool autoclose);
      ~file_input_port();

      Long backend_read_some(bytes_ref) override;
  };

}

#endif
