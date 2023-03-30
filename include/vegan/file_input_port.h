#ifndef VEGAN_FILE_INPUT_PORT_H
#define VEGAN_FILE_INPUT_PORT_H

#include <vegan/bytes_ref.h>
#include <vegan/input_port.h>
#include <vegan/io_buffer.h>
#include <vegan/file_port.h>

namespace vegan {

  class file_input_port: public file_port, public input_port {
    public:
      file_input_port() {}
      explicit file_input_port(int fd, int lookahead = 0);
      ~file_input_port();

      Long read_some(bytes_ref) override;
      bool unread(const_bytes_ref) override;

    private:
      io_buffer buf;
  };

}

#endif
