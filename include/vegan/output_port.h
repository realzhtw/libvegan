#ifndef VEGAN_OUTPUT_PORT_H
#define VEGAN_OUTPUT_PORT_H

#include <vegan/bytes_ref.h>
#include <vegan/io_buffer.h>

namespace vegan {

  class output_port {
    public:
      explicit output_port(Long block_size = 0);
      virtual ~output_port() {}

      virtual Long backend_write_some(const_bytes_ref) = 0;

      Long write_some(const_bytes_ref src) { return obuf.size() == 0 ? backend_write_some(src) : buffered_write_some(src); }
      void flush();

    private:
      Long buffered_write_some(const_bytes_ref);

    private:
      io_buffer obuf;
  };

}

#endif
