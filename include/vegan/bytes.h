#ifndef VEGAN_BYTES_H
#define VEGAN_BYTES_H

#include <vegan/types.h>
#include <vegan/bytes_ref.h>
#include <vegan/exception.h>

namespace vegan {

  class bad_alloc: public exception {};

  class bytes {
    public:
      bytes() {}
      explicit bytes(Long n);
      explicit bytes(Long n, byte);
      bytes(bytes &&b): impl{b.impl} { b.impl = bytes_ref{}; }
      bytes(const_bytes_ref b);
      bytes(const bytes &) = delete;
      ~bytes() { free(); }

      bytes &operator=(const bytes &) = delete;
      bytes &operator=(bytes &&b) { free(); impl = b.impl; b.impl = bytes_ref{}; return *this; }

            byte *ptr(Long i = 0)       { return impl.ptr(i); }
      const byte *ptr(Long i = 0) const { return impl.ptr(i); }
      Long size() const { return impl.size(); }

      const byte &operator[](Long i) const { return *ptr(i); }
            byte &operator[](Long i)       { return *ptr(i); }

    private:
      void free();

    private:
      bytes_ref impl;
  };

  inline       bytes_ref drop_first(      bytes &b, Long n = 1) { return drop_first(      bytes_ref{b}, n); }
  inline const_bytes_ref drop_first(const bytes &b, Long n = 1) { return drop_first(const_bytes_ref{b}, n); }
  inline       bytes_ref drop_last(      bytes &b, Long n = 1) { return drop_last(      bytes_ref{b}, n); }
  inline const_bytes_ref drop_last(const bytes &b, Long n = 1) { return drop_last(const_bytes_ref{b}, n); }
  inline       bytes_ref first_n(      bytes &b, Long n) { return first_n(      bytes_ref{b}, n); }
  inline const_bytes_ref first_n(const bytes &b, Long n) { return first_n(const_bytes_ref{b}, n); }
  inline       bytes_ref last_n(      bytes &b, Long n) { return last_n(      bytes_ref{b}, n); }
  inline const_bytes_ref last_n(const bytes &b, Long n) { return last_n(const_bytes_ref{b}, n); }
  inline       bytes_ref cut(      bytes &b, Long i) { return cut(      bytes_ref{b}, i); }
  inline const_bytes_ref cut(const bytes &b, Long i) { return cut(const_bytes_ref{b}, i); }
  inline       bytes_ref cut(      bytes &b, Long i, Long n) { return cut(      bytes_ref{b}, i, n); }
  inline const_bytes_ref cut(const bytes &b, Long i, Long n) { return cut(const_bytes_ref{b}, i, n); }

  template<typename T> span<      T> as_span(      bytes &x) { return as_span<      T>(span<      byte>{x}); }
  template<typename T> span<const T> as_span(const bytes &x) { return as_span<const T>(span<const byte>{x}); }

  template<> inline span<      byte>::span(      bytes &b): span{b.ptr(), b.size()} {}
  template<> inline span<const byte>::span(      bytes &b): span{b.ptr(), b.size()} {}
  template<> inline span<const byte>::span(const bytes &b): span{b.ptr(), b.size()} {}

}

#endif
