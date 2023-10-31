#ifndef VEGAN_STRING_REF_H
#define VEGAN_STRING_REF_H

#include <vegan/bytes_ref.h>
#include <vegan/rune.h>

namespace vegan {

  class string;
  class const_bytes_ref;

  class string_ref {
    public:
      string_ref() {}
      string_ref(const char *);
      string_ref(const string &);
      explicit string_ref(const_bytes_ref b): impl{b} {}

      const byte *ptr() const { return impl.ptr(); }
      Long size() const { return impl.size(); }
      bool empty() const { return size() == 0; }

      const_bytes_ref &as_bytes()       { return impl; }
      const_bytes_ref  as_bytes() const { return impl; }

    private:
      const_bytes_ref impl;
  };

  class c_string_ref {
    public:
      c_string_ref() {}
      c_string_ref(const char *s): p{s} {}
      c_string_ref(const string &);

      const byte *ptr() const { return reinterpret_cast<const byte *>(p); }

    private:
      const char *p = nullptr;
  };

  inline int compare(string_ref a, string_ref b) { return compare(a.as_bytes(), b.as_bytes()); }
  inline bool operator<(string_ref a, string_ref b) { return compare(a, b) < 0; }
  inline bool operator<=(string_ref a, string_ref b) { return compare(a, b) < 1; }
  inline bool operator>(string_ref a, string_ref b) { return compare(a, b) > 0; }
  inline bool operator>=(string_ref a, string_ref b) { return compare(a, b) > -1; }
  inline bool operator==(string_ref a, string_ref b) { return compare(a, b) == 0; }

  bool has_prefix(string_ref, string_ref);
  bool has_suffix(string_ref, string_ref);

  Long find(string_ref, char);
  Long find(string_ref, rune);

}

#endif
