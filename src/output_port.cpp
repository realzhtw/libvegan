#include <vegan/output_port.h>

namespace vegan {

  output_port::output_port(Long block_size): obuf{block_size} {}

  void output_port::flush()
  {
    auto data = obuf.data();
    while (data.size() > 0)
      data.drop_first(backend_write_some(data));
    obuf.reset();
  }

  Long output_port::write_some(const_bytes_ref src)
  {
    if (obuf.size() == 0)
      return backend_write_some(src);

    if (obuf.empty() && src.size() > obuf.size())
      return backend_write_some(first_n(src, obuf.size())); // avoid buffer

    auto n = obuf.write_some(src);
    if (obuf.full()) flush();
    return n;
  }


}
