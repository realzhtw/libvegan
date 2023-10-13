#include <vegan/io_buffer.h>
#include <vegan/utils.h>

namespace vegan {

  void io_buffer::resize(Long n) { b = bytes{n}; i = j = 0; }

  void io_buffer::reset(int keep)
  {
    auto n = min(rdpos(), keep);
    copy(b.ptr(keep - n), rdptr(), n);
    i = j = keep;
  }

}
