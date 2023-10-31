#ifndef VEGAN_STRING_H
#define VEGAN_STRING_H

#include <vegan/bytes.h>
#include <vegan/string_ref.h>

namespace vegan {

  class string {
    public:
      string(): string("") {}
      explicit string(Long);
      string(const char *);
      explicit string(const_bytes_ref);
      string(string_ref s): string{s.as_bytes()} {}
      string(const string &s): string{s.as_bytes()} {}
      string(string &&s): impl{move(s.impl)} {}

      string &operator=(const string &);
      string &operator=(string &&s) { impl = move(s.impl); return *this; }

            byte *ptr()       { return impl.ptr(); }
      const byte *ptr() const { return impl.ptr(); }
      const char *c_str() const { return reinterpret_cast<const char *>(ptr()); }

      Long size() const { return impl.size() - 1; }

            bytes_ref as_bytes()       { return first_n(bytes_ref{impl}, size()); }
      const_bytes_ref as_bytes() const { return first_n(impl, size()); }

    private:
      bytes impl;
  };

  string operator+(string_ref, string_ref);

  string to_string(short);
  string to_string(unsigned short);
  string to_string(int);
  string to_string(unsigned);
  string to_string(long);
  string to_string(unsigned long);
  string to_string(long long);
  string to_string(unsigned long long);

  inline string_ref::string_ref(const string &s): string_ref{s.as_bytes()} {}

}

#endif
