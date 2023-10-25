#include <vegan/string.h>
#include <vegan/c_string.h>
#include <vegan/utils.h>

namespace vegan {

  string::string(Long n): impl{n+1} {}

  string::string(const char *s): string{s, c_string_length(s)} {}

  string::string(const char *p, Long n): string{n}
  {
    copy(impl.ptr(), string_ref{p, n}.as_bytes());
    impl[n] = '\0';
  }

  string operator+(string_ref a, string_ref b)
  {
    string s{a.size() + b.size()};
    copy(s.as_bytes().ptr(), a.as_bytes());
    copy(s.as_bytes().ptr(a.size()), b.as_bytes());
    return s;
  }

  string_ref::string_ref(const char *s): string_ref{s, c_string_length(s)} {}

  const_bytes_ref string_ref::as_bytes() const { return const_bytes_ref{(const byte *)p, n}; }

  int compare(string_ref a, string_ref b) { return compare(a.as_bytes(), b.as_bytes()); }

  bool has_prefix(string_ref s, string_ref pref)
  {
    return first_n(s.as_bytes(), pref.size()) == pref.as_bytes();
  }

  bool has_suffix(string_ref s, string_ref suff)
  {
    return last_n(s.as_bytes(), suff.size()) == suff.as_bytes();
  }

}
