#ifndef VEGAN_FILE_OUTPUT_PORT_H
#define VEGAN_FILE_OUTPUT_PORT_H

#include <vegan/bytes_ref.h>
#include <vegan/output_port.h>
#include <vegan/bytes.h>
#include <vegan/fdport.h>

namespace vegan {

  class file_output_port: public fdport, public output_port {
    public:
      file_output_port() {}
      explicit file_output_port(int fd, Long buffer_size, bool autoclose);
      ~file_output_port();

      Long write_some(const_bytes_ref) override;
      void flush() override;
      void close() override;
    private:
      bytes buf;
      Long buf_wrpos = 0;
  };

  file_output_port open_output_file(string_ref path);

}

#endif
