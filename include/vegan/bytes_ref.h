#ifndef VEGAN_BYTES_REF_H
#define VEGAN_BYTES_REF_H

#include <vegan/types.h>
#include <vegan/utils.h>
#include <vegan/span.h>

namespace vegan {

  class bytes;

  class string_ref;

  typedef span<byte> bytes_ref;
  typedef span<const byte> const_bytes_ref;

  template<Long N>
    bytes_ref first_n(byte (&b)[N], Long n) { return first_n(bytes_ref{b}, n); }
  template<Long N>
    const_bytes_ref first_n(const byte (&b)[N], Long n) { return first_n(const_bytes_ref{b}, n); }

  int compare(const_bytes_ref, const_bytes_ref);
  inline bool operator<(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) < 0; }
  inline bool operator<=(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) < 1; }
  inline bool operator>(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) > 0; }
  inline bool operator>=(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) > -1; }
  inline bool operator==(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) == 0; }

  void copy(byte *dst, const_bytes_ref);
  Long copy(bytes_ref dst, const_bytes_ref);

  Long find(const_bytes_ref, byte);

}

#endif
