#ifndef VEGAN_FILE_INPUT_PORT_H
#define VEGAN_FILE_INPUT_PORT_H

#include <vegan/bytes_ref.h>
#include <vegan/input_port.h>
//#include <vegan/input_buffer.h>
#include <vegan/io_buffer.h>
#include <vegan/file_port.h>

namespace vegan {

  class file_input_port: public file_port, public input_port {
    public:
      file_input_port() {}
      explicit file_input_port(int fd, int lookahead = 0);
      explicit file_input_port(string_ref path);
      ~file_input_port();

      Long read(byte *, Long) override;
      bool unread(const byte *, Long) override;

    private:
      io_buffer buf;
  };

  class unbuffered_file_input_port: public file_port, public unbuffered_input_port {
    public:
      unbuffered_file_input_port() {}
      ~unbuffered_file_input_port();

      Long read(byte *, Long) override;
    
    private:
  };

}

#endif
