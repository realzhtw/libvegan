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

      const_bytes_ref slice(Long i) const { return impl.slice(i); }
            bytes_ref slice(Long i)       { return impl.slice(i); }
      const_bytes_ref slice(Long i, Long n) const { return impl.slice(i, n); }
            bytes_ref slice(Long i, Long n)       { return impl.slice(i, n); }
      const_bytes_ref first_n(Long n) const { return impl.first_n(n); }
            bytes_ref first_n(Long n)       { return impl.first_n(n); }
      const_bytes_ref last_n(Long n) const { return impl.last_n(n); }
            bytes_ref last_n(Long n)       { return impl.last_n(n); }

      template<typename T>
        vector_ref<T> as_vector() { return impl.as_vector<T>(); }

      template<typename T>
        const_vector_ref<T> as_vector() const { return impl.as_vector<T>(); }
      
    private:
      void free();

    private:
      bytes_ref impl;
  };

  inline bytes_ref::bytes_ref(bytes &b): bytes_ref{b.ptr(), b.size()} {}
  inline const_bytes_ref::const_bytes_ref(const bytes &b): const_bytes_ref{b.ptr(), b.size()} {}

  void copy(byte *dst, const byte *, Long);
  void copy(byte *dst, const_bytes_ref);

}

#endif
