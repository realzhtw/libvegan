#include <vegan/bytes_ref.h>
#include <vegan/string_ref.h>

namespace vegan {

  string_ref bytes_ref::as_string() const { return string_ref{(char *)ptr(), size()}; }

  string_ref const_bytes_ref::as_string() const { return string_ref{(char *)ptr(), size()}; }

}

