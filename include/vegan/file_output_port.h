#ifndef VEGAN_FILE_OUTPUT_PORT_H
#define VEGAN_FILE_OUTPUT_PORT_H

#include <vegan/bytes_ref.h>
#include <vegan/output_port.h>
#include <vegan/output_buffer.h>
#include <vegan/file_port.h>

namespace vegan {

  class file_output_port: private file_port, public output_port {
    public:
      file_output_port() {}
      ~file_output_port();
      explicit file_output_port(int fd);
      explicit file_output_port(const_string_ref path);

      void open(const_string_ref path);

      void write(const_bytes_ref) override;
      void flush() override;
      void close();
    private:
      output_buffer output_buf;
  };

}

#endif
