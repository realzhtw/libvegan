#include <vegan/output_buffer.h>
#include <vegan/utils.h>

namespace vegan {

  Long output_buffer::write(const_bytes_ref x)
  {
    auto n = min(x.size(), bytes_left());
    copy(b.ptr(i), x.first_n(n));
    i += n;
    return n;
  }

}
