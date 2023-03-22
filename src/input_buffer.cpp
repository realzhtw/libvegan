#include <vegan/input_buffer.h>
#include <vegan/utils.h>

namespace vegan {

  Long input_buffer::read(bytes_ref x)
  {
    auto n = peek(x);
    advance(n);
    return n;
  }

  Long input_buffer::peek(bytes_ref x)
  {
    auto n = min(x.size(), bytes_available());
    copy(x.ptr(), data().first_n(n));
    return n;
  }

  Long input_buffer::advance(Long n)
  {
    auto k = min(n, bytes_available());
    i += k;
    return k;
  }

}
