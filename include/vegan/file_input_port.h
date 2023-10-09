#ifndef VEGAN_FILE_INPUT_PORT_H
#define VEGAN_FILE_INPUT_PORT_H

#include <vegan/bytes.h>
#include <vegan/input_port.h>
#include <vegan/fdport.h>

namespace vegan {

  class file_input_port: public fdport, public input_port {
    public:
      file_input_port() {}
      explicit file_input_port(int fd, bool buffered, bool autoclose);
      ~file_input_port();

      Long read_some(bytes_ref) override;
      bool unread(const_bytes_ref) override;

    private:
      Long block_size = 0;
      bytes buf;
      Long buf_rdpos = 0;
      Long buf_end = 0;
  };

}

#endif
