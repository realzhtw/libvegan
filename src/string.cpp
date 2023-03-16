#include <vegan/string.h>
#include <vegan/c_string.h>

namespace vegan {

  string::string(const_string_ref s): impl{s.size()+1}
  {
    copy(impl.ptr(), s.as_bytes());
  }

  string::string(const char *p, Long n): string{const_string_ref{p, n}} {}

  const_string_ref::const_string_ref(const char *s): const_string_ref{s, c_string_length(s)} {}

}
