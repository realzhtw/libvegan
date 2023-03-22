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
      template<Long n> string_ref(const char s[n]): p{s}, n{n} {}
      string_ref(const string &);
      explicit string_ref(const char *p, Long n): p{p}, n{n} {}

      const char *ptr() { return p; }
      Long size() const { return n; }

      const_bytes_ref as_bytes() const;

    private:
      const char *p = nullptr;
      Long        n = 0;
  };

}

#endif
