#include <vegan/input_port.h>
#include <vegan/utils.h>

namespace {
  const auto max_backoff = 8; // 6 for utf8 rounded up to power of 2
}

namespace vegan {

  input_port::input_port(Long block_size): block_size{block_size}, ibuf{block_size + max_backoff} {}


  Long input_port::read_from_buffer(bytes_ref dst)
  {
    auto n = copy(dst, ibuf.data());
    ibuf.advance_rdpos(n);
    return n;
  }

  Long input_port::buffered_read_some(bytes_ref dst)
  {
    if (ibuf.empty()) {
      ibuf.reset(max_backoff);
      if (dst.size() >= block_size) {
        auto n = backend_read_some({dst.ptr(), block_size});
        auto b = min(n, max_backoff);
        //copy(ibuf.rdptr() - b, dst.ptr(n - b), b);
        copy(ibuf.rdptr() - b, cut(dst, n - b, b));
        return n;
      }
      auto n = backend_read_some({ibuf.wrptr(), ibuf.space_left()});
      if (n == 0) return 0;
      ibuf.advance_wrpos(n);
    }
    return read_from_buffer(dst);
  }

}
