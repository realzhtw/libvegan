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
      bytes_ref(byte& b): impl{&b, 1} {}
      bytes_ref(byte *p, Long n): impl{p, n} {}
      template<Long n> bytes_ref(byte (&b)[n]): impl{b, n} {}

      byte *ptr(Long i = 0) const { return impl.p + i; }
      Long size() const { return impl.n; }

      byte &operator[](Long i) const { return *ptr(i); }

      void drop_first(Long n) { impl.p += n; impl.n -= n; }

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
      const_bytes_ref(const byte &b): impl{&b, 1} {}
      const_bytes_ref(const byte *p, Long n): impl{p, n} {}
      template<Long n> const_bytes_ref(const byte (&b)[n]): impl{b, n} {}
      const_bytes_ref(const bytes_ref &b): impl{b.ptr(), b.size()} {}

      const byte *ptr(Long i = 0) const { return impl.p + i; }
      Long size() const { return impl.n; }

      const byte &operator[](Long i) const { return *ptr(i); }

      void drop_first(Long n) { impl.p += n; impl.n -= n; }

      template<typename T> const_vector_ref<T> as_vector() const;

      string_ref as_string() const;
 
    private:
      struct Impl {
        const byte *p = nullptr;
        Long        n = 0;
      } impl;
  };

  inline       bytes_ref cut(      bytes_ref b, Long i, Long n) { return {b.ptr(i), n}; }
  inline const_bytes_ref cut(const_bytes_ref b, Long i, Long n) { return {b.ptr(i), n}; }
  inline       bytes_ref first_n(      bytes_ref b, Long n) { return cut(b, 0, n); }
  inline const_bytes_ref first_n(const_bytes_ref b, Long n) { return cut(b, 0, n); }

  int compare(const_bytes_ref, const_bytes_ref);
  inline bool operator<(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) < 0; }
  inline bool operator<=(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) < 1; }
  inline bool operator>(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) > 0; }
  inline bool operator>=(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) > -1; }
  inline bool operator==(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) == 0; }

  void copy(byte *dst, const byte *, Long);
  void copy(byte *dst, const_bytes_ref);

}

#endif
