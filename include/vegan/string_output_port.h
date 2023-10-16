#ifndef VEGAN_STRING_OUTPUT_PORT_H
#define VEGAN_STRING_OUTPUT_PORT_H

#include <vegan/output_port.h>
#include <vegan/string_buf.h>
#include <vegan/string.h>

namespace vegan {

  class string_output_port: public output_port {
    public:
      string_output_port() {}
      Long backend_write_some(const_bytes_ref) override;

      string_ref data() const { return strbuf.data(); }

    private:
      string_buf strbuf;
  };

  template<typename F>
    string with_output_to_string(F &&f)
    {
      string_output_port p;
      with_output_to(p, f);
      return p.data();
    }

}

#endif
