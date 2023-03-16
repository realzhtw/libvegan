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
      bytes(const bytes &) = delete;
      ~bytes() { free(); }

      bytes &operator=(const bytes &) = delete;
      bytes &operator=(bytes &&b) { free(); impl = b.impl; b.impl = bytes_ref{}; return *this; }

            Byte *ptr(Long i = 0)       { return impl.ptr(i); }
      const Byte *ptr(Long i = 0) const { return impl.ptr(i); }
      Long size() const { return impl.size(); }

      const Byte &operator[](Long i) const { return *ptr(i); }
            Byte &operator[](Long i)       { return *ptr(i); }

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

  void copy(Byte *dst, const_bytes_ref);

}

#endif
