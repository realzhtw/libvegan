#ifndef VEGAN_FILE_OUTPUT_PORT_H
#define VEGAN_FILE_OUTPUT_PORT_H

#include <vegan/bytes_ref.h>
#include <vegan/output_port.h>
#include <vegan/io_buffer.h>
#include <vegan/file_port.h>

namespace vegan {

  class file_output_port: public file_port, public output_port {
    public:
      file_output_port() {}
      explicit file_output_port(int fd);
      ~file_output_port();

      Long write_some(const byte *, Long) override;
      void flush() override;
      void close() override;
    private:
      io_buffer buf;
  };

  file_output_port open_output_file(string_ref path);

  class unbuffered_file_output_port: public file_port, public unbuffered_output_port {
    public:
      unbuffered_file_output_port() {}
      explicit unbuffered_file_output_port(int fd);
      ~unbuffered_file_output_port();

      Long write_some(const byte *, Long) override;
      //void close() override;

    private:
  };

}

#endif
