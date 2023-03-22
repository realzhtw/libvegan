#include <vegan/string_ref.h>
#include <vegan/bytes_ref.h>

namespace vegan {

  const_bytes_ref string_ref::as_bytes() const { return const_bytes_ref{(const byte *)p, n}; }

}

