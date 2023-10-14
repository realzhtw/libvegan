#ifndef VEGAN_STRING_OUTPUT_PORT_H
#define VEGAN_STRING_OUTPUT_PORT_H

#include <vegan/output_port.h>
#include <vegan/string_buf.h>

namespace vegan {

  class string_output_port: public output_port {
    public:
      string_output_port() {}
      Long backend_write_some(const_bytes_ref) override;

      string_ref data() const { return strbuf.data(); }

    private:
      string_buf strbuf;
  };
}

#endif
