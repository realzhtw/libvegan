#include <vegan/bytes.h>
#include <vegan/platform/alloc.h>

namespace vegan {

  bytes::bytes(Long n)
  {
    byte *p = (byte *)platform::alloc(n);
    if (p == nullptr)
      throw bad_alloc{};
    impl = bytes_ref{p, n};
  }

  bytes::bytes(const_bytes_ref b): bytes{b.size()} { copy(ptr(), b); }

  void bytes::free()
  {
    platform::free(impl.ptr());
    impl = bytes_ref{};
  }

  void copy(byte *dst, const byte *src, Long n)
  {
    while (n-- > 0)
      *dst++ = *src++;
  }

  void copy(byte *dst, const_bytes_ref b) { copy(dst, b.ptr(), b.size()); }

}
