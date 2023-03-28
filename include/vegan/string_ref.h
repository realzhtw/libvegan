#ifndef VEGAN_STRING_REF_H
#define VEGAN_STRING_REF_H

#include <vegan/types.h>

namespace vegan {

  class string;
  class const_bytes_ref;

  class string_ref {
    public:
      string_ref() {}
      string_ref(const char *);
      string_ref(const string &);
      explicit string_ref(const char *p, Long n): p{p}, n{n} {}

      const char *ptr() const { return p; }
      Long size() const { return n; }

      const_bytes_ref as_bytes() const;

    private:
      const char *p = nullptr;
      Long        n = 0;
  };

  class c_string_ref {
    public:
      c_string_ref() {}
      c_string_ref(const char *s): p{s} {}
      c_string_ref(const string &);

      const char *ptr() const { return p; }

    private:
      const char *p = nullptr;
  };

}

#endif
