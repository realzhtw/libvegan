#include <vegan/string_output_port.h>

namespace vegan {

  Long string_output_port::backend_write_some(const_bytes_ref src)
  {
    strbuf.append(src);
    return src.size();
  }

}
