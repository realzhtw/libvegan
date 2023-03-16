#include <vegan/bytes.h>
#include <vegan/platform/alloc.h>

namespace vegan {

  bytes::bytes(Long n)
  {
    Byte *p = (Byte *)platform::alloc(n);
    if (p == nullptr)
      throw bad_alloc{};
    impl = bytes_ref{p, n};
  }

  void bytes::free()
  {
    platform::free(impl.ptr());
    impl = bytes_ref{};
  }

  void copy(Byte *dst, const Byte *src, Long n)
  {
    while (n-- > 0)
      *dst++ = *src++;
  }

  void copy(Byte *dst, const_bytes_ref b) { copy(dst, b.ptr(), b.size()); }

}
