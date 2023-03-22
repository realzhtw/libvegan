#ifndef VEGAN_BYTES_REF_H
#define VEGAN_BYTES_REF_H

#include <vegan/types.h>

namespace vegan {

  class bytes;

  class string_ref;

  template<typename T> class vector_ref;
  template<typename T> class const_vector_ref;

  class bytes_ref {
    public:
      bytes_ref() {}
      bytes_ref(bytes &b);
      explicit bytes_ref(byte *p, Long n): impl{p, n} {}
      template<Long n> bytes_ref(byte (&b)[n]): impl{b, n} {}

      byte *ptr(Long i = 0) const { return impl.p + i; }
      Long size() const { return impl.n; }
      bool empty() const { return size() == 0; }

      byte &operator[](Long i) const { return *ptr(i); }

      void drop_first(Long n) { impl.p += n; impl.n -= n; }

      bytes_ref slice(Long i)         const { return bytes_ref{ptr(i), size() - i}; }
      bytes_ref slice(Long i, Long n) const { return bytes_ref{ptr(i), n}; }

      bytes_ref first_n(Long n) const { return slice(0, n); }
      bytes_ref last_n(Long n) const { return slice(size() - n, n); }

      template<typename T> vector_ref<T> as_vector() const;

      string_ref as_string() const;

    private:
      struct Impl {
        byte *p = nullptr;
        Long  n = 0;
      } impl;
  };

  class const_bytes_ref {
    public:
      const_bytes_ref() {}
      const_bytes_ref(const bytes &b);
      explicit const_bytes_ref(const byte *p, Long n): impl{p, n} {}
      template<Long n> const_bytes_ref(const byte (&b)[n]): impl{b, n} {}
      //template<Long n> const_bytes_ref(byte b[n]): impl{b, n} {}
      const_bytes_ref(const bytes_ref &b): impl{b.ptr(), b.size()} {}

      const byte *ptr(Long i = 0) const { return impl.p + i; }
      Long size() const { return impl.n; }
      bool empty() const { return size() == 0; }

      const byte &operator[](Long i) const { return *ptr(i); }

      void drop_first(Long n) { impl.p += n; impl.n -= n; }

      const_bytes_ref slice(Long i)         const { return const_bytes_ref{ptr(i), size() - i}; }
      const_bytes_ref slice(Long i, Long n) const { return const_bytes_ref{ptr(i), n}; }

      const_bytes_ref first_n(Long n) const { return slice(0, n); }
      const_bytes_ref last_n(Long n) const { return slice(size() - n, n); }

      template<typename T> const_vector_ref<T> as_vector() const;

      string_ref as_string() const;
 
    private:
      struct Impl {
        const byte *p = nullptr;
        Long        n = 0;
      } impl;
  };

}

#endif
