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

      template<typename T>
        vector_ref<T> as_vector() { return impl.as_vector<T>(); }

      template<typename T>
        const_vector_ref<T> as_vector() const { return impl.as_vector<T>(); }
      
    private:
      void free();

    private:
      bytes_ref impl;
  };

  inline       bytes_ref drop_last(      bytes &b, Long n = 1) { return drop_last(      bytes_ref{b}, n); }
  inline const_bytes_ref drop_last(const bytes &b, Long n = 1) { return drop_last(const_bytes_ref{b}, n); }

  inline bytes_ref::bytes_ref(bytes &b): bytes_ref{b.ptr(), b.size()} {}
  inline const_bytes_ref::const_bytes_ref(const bytes &b): const_bytes_ref{b.ptr(), b.size()} {}

}

#endif
