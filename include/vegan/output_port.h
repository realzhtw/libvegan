#ifndef VEGAN_OUTPUT_PORT_H
#define VEGAN_OUTPUT_PORT_H

#include <vegan/bytes_ref.h>

namespace vegan {

  class output_port {
    public:
      virtual void write(const_bytes_ref) = 0;
      virtual void flush() = 0;

      virtual ~output_port() {}
  };

  class unbuffered_output_port: public output_port {
    public:
      void flush() override {}
  };

}

#endif
