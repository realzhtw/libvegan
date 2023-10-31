#include <vegan/string.h>
#include <vegan/c_string.h>
#include <vegan/utils.h>
#include <vegan/utf8.h>

namespace vegan {

  string::string(Long n): impl{n+1} {}

  string::string(const char *s): string{string_ref{s}} {}

  string::string(const_bytes_ref b): string{b.size()}
  {
    copy(impl.ptr(), b);
    impl[impl.size()-1] = '\0';
  }

  string operator+(string_ref a, string_ref b)
  {
    string s{a.size() + b.size()};
    copy(s.as_bytes().ptr(), a.as_bytes());
    copy(s.as_bytes().ptr(a.size()), b.as_bytes());
    return s;
  }

  string_ref::string_ref(const char *s):
    string_ref{const_bytes_ref{reinterpret_cast<const byte *>(s), c_string_length(s)}} {}

  bool has_prefix(string_ref s, string_ref pref)
  {
    return first_n(s.as_bytes(), pref.size()) == pref.as_bytes();
  }

  bool has_suffix(string_ref s, string_ref suff)
  {
    return last_n(s.as_bytes(), suff.size()) == suff.as_bytes();
  }

  Long find(string_ref s, char c) { return find(s.as_bytes(), (byte)c); }

  Long find(string_ref s, rune r)
  {
    auto b = s.as_bytes();
    byte buf[6];
    auto n = utf8::encode_rune(r, buf);
    for (Long i = 0; i < s.size() - n + 1; ++i) {
      int j = 0;
      while (j < n && b[i+j] == buf[j])
        ++j;
      if (j == n)
        return i;
    }
    return s.size();
  }

}
