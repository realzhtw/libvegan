#ifndef VEGAN_INPUT_PORT_H
#define VEGAN_INPUT_PORT_H

#include <vegan/types.h>
#include <vegan/io_buffer.h>

namespace vegan {

  class input_port {
    public:
      explicit input_port(Long block_size = 0);
      virtual ~input_port() {}
      virtual Long backend_read_some(bytes_ref) = 0;

      Long read_some(bytes_ref dst) { return ibuf.size() == 0 ? backend_read_some(dst) : buffered_read_some(dst); }
      bool back_off(int n) { bool r = n <= ibuf.rdpos(); if (r) ibuf.backoff_rdpos(n); return r; }

    private:
      Long buffered_read_some(bytes_ref);
      Long read_from_buffer(bytes_ref);

    private:
      Long block_size;
      io_buffer ibuf;
  };

}

#endif
