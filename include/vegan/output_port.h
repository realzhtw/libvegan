#ifndef VEGAN_OUTPUT_PORT_H
#define VEGAN_OUTPUT_PORT_H

#include <vegan/bytes_ref.h>
#include <vegan/output_buffer.h>

namespace vegan {

  class output_port {
    public:
      explicit output_port(Long block_size = 0);
      virtual ~output_port() {}

      virtual Long backend_write_some(const_bytes_ref) = 0;

      Long write_some(const_bytes_ref src);
      void flush();

    private:
      output_buffer obuf;
  };

}

#endif
