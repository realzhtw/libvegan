#include <vegan/string.h>
#include <vegan/c_string.h>
#include <vegan/utils.h>

namespace vegan {

  string::string(const char *s): string{s, c_string_length(s)} {}

  string::string(const char *p, Long n): impl{n+1}
  {
    copy(impl.ptr(), reinterpret_cast<const byte *>(p), n);
    impl[n] = '\0';
  }

  string::string(string_ref s): string{s.ptr(), s.size()} {}

  string_ref::string_ref(const char *s): string_ref{s, c_string_length(s)} {}

  const_bytes_ref string_ref::as_bytes() const { return const_bytes_ref{(const byte *)p, n}; }

  int compare(string_ref a, string_ref b) { return compare(a.as_bytes(), b.as_bytes()); }

  bool has_prefix(string_ref s, string_ref prefix)
  {
    return size(s) > size(prefix) && first_n(s.as_bytes(), prefix.size()) == prefix.as_bytes();
  }

}
