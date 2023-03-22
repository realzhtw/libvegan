#ifndef VEGAN_STRING_H
#define VEGAN_STRING_H

#include <vegan/bytes.h>
#include <vegan/string_ref.h>

namespace vegan {

  class string {
    public:
      string() {}
      string(const char *);
      explicit string(const char *, Long n);
      explicit string(string_ref s);
      string(const string &);
      string(string &&);

      string &operator=(const string &);
      string &operator=(string &&);

            char *ptr()       { return (char *)impl.ptr(); }
      const char *ptr() const { return (char *)impl.ptr(); }

      Long size() const { return impl.size(); }

            bytes_ref as_bytes()       { return impl; }
      const_bytes_ref as_bytes() const { return impl; }

    private:
      bytes impl;
  };

  string to_string(short);
  string to_string(unsigned short);
  string to_string(int);
  string to_string(unsigned);
  string to_string(long);
  string to_string(unsigned long);
  string to_string(long long);
  string to_string(unsigned long long);

  inline string_ref::string_ref(const string &s): p{s.ptr()}, n{s.size()} {}

}

#endif
