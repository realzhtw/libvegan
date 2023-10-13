#include <vegan/output_port.h>
#include <vegan/utils.h>

namespace vegan {

  output_port::output_port(Long block_size): obuf{block_size} {}

  void output_port::flush()
  {
    while (!obuf.empty()) {
      auto n = backend_write_some(obuf.data());
      obuf.advance_rdpos(n);
    }
    obuf.reset();
  }

  Long output_port::buffered_write_some(const_bytes_ref src)
  {
    if (obuf.empty() && src.size() > obuf.size())
      return backend_write_some(first_n(src, obuf.size())); // avoid buffer

    auto n = min(src.size(), obuf.space_left());
    copy(obuf.wrptr(), first_n(src, n));
    obuf.advance_wrpos(n);

    if (obuf.full()) flush();

    return n;
  }


}
