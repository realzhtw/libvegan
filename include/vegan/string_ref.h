#ifndef VEGAN_STRING_REF_H
#define VEGAN_STRING_REF_H

#include <vegan/types.h>
#include <vegan/bytes_ref.h>

namespace vegan {

  class string;

  class string_ref {
    public:
      string_ref() {}
      string_ref(string &);
      explicit string_ref(char *p, Long n): p{p}, n{n} {}

      Long size() const { return n; }

      bytes_ref as_bytes() const { return bytes_ref{(Byte *)p, n}; }

    private:
      char *p = nullptr;
      Long  n = 0;
  };

  class const_string_ref {
    public:
      const_string_ref(const string &);
      const_string_ref(const char *);
      explicit const_string_ref(const char *p, Long n): p{p}, n{n} {}

      Long size() const { return n; }

      const_bytes_ref as_bytes() const { return const_bytes_ref{(Byte *)p, n}; }

    private:
      const char *p = nullptr;
      Long        n = 0;
  };

}

#endif
