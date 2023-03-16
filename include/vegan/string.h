#ifndef VEGAN_STRING_H
#define VEGAN_STRING_H

#include <vegan/bytes.h>
#include <vegan/string_ref.h>

namespace vegan {

  class string {
    public:
      string() {}
      string(const char *);
      explicit string(const_string_ref);
      explicit string(const char *, Long n);
      string(const string &);
      string(string &&);

            char *ptr()       { return (char *)impl.ptr(); }
      const char *ptr() const { return (char *)impl.ptr(); }

      Long size() const { return impl.size(); }

      string &operator=(const string &);
      string &operator=(string &&);

    private:
      bytes impl;
  };

  string to_string(int);

  inline string_ref::string_ref(string &s): p{s.ptr()}, n{s.size()} {}
  inline const_string_ref::const_string_ref(const string &s): p{s.ptr()}, n{s.size()} {}

}

#endif
