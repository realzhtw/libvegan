#include <vegan/string.h>
#include <vegan/c_string.h>

namespace vegan {

  string::string(const char *p, Long n): impl{n+1}
  {
    copy(impl.ptr(), reinterpret_cast<const byte *>(p), n);
    impl[n] = '\0';
  }

  string::string(string_ref s): string{s.ptr(), s.size()} {}

  string_ref::string_ref(const char *s): string_ref{s, c_string_length(s)} {}

}
