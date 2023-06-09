#include <vegan/bytes.h>
#include <vegan/platform/alloc.h>
#include <vegan/utils.h>
#include <vegan/string_ref.h>

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

  string_ref bytes_ref::as_string() const { return string_ref{(char *)ptr(), size()}; }

  string_ref const_bytes_ref::as_string() const { return string_ref{(char *)ptr(), size()}; }

  void copy(byte *dst, const byte *src, Long n) { while (n-- > 0) *dst++ = *src++; }

  void copy(byte *dst, const_bytes_ref b) { copy(dst, b.ptr(), b.size()); }

  int compare(const_bytes_ref a, const_bytes_ref b)
  {
    auto n = min(a.size(), b.size());
    for (auto i = 0; i != n; ++i)
      if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;

    return a.size() < b.size() ? -1 :
           a.size() > b.size() ?  1 : 0;
  }

}
