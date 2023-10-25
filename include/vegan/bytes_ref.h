#ifndef VEGAN_BYTES_REF_H
#define VEGAN_BYTES_REF_H

#include <vegan/types.h>
#include <vegan/utils.h>

namespace vegan {

  class bytes;

  class string_ref;

  template<typename T> class vector_ref;
  template<typename T> class const_vector_ref;

  class bytes_ref {
    public:
      bytes_ref() {}
      bytes_ref(bytes &b);
      explicit bytes_ref(byte& b): impl{&b, 1} {}
      bytes_ref(byte *p, Long n): impl{p, n} {}
      template<Long n> bytes_ref(byte (&b)[n]): impl{b, n} {}
      bytes_ref(const bytes_ref &b): impl{b.ptr(), b.size()} {}

      byte *ptr(Long i = 0) const { return impl.p + i; }
      Long size() const { return impl.n; }

      void drop_first(Long n) { impl.p += n; impl.n -= n; }

      byte &operator[](Long i) const { return *ptr(i); }

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
      explicit const_bytes_ref(const byte &b): impl{&b, 1} {}
      const_bytes_ref(const byte *p, Long n): impl{p, n} {}
      template<Long n> const_bytes_ref(const byte (&b)[n]): impl{b, n} {}
      const_bytes_ref(const bytes_ref &b): impl{b.ptr(), b.size()} {}

      const byte *ptr(Long i = 0) const { return impl.p + i; }
      Long size() const { return impl.n; }

      void drop_first(Long n) { impl.p += n; impl.n -= n; }

      const byte &operator[](Long i) const { return *ptr(i); }

      template<typename T> const_vector_ref<T> as_vector() const;

      string_ref as_string() const;
 
    private:
      struct Impl {
        const byte *p = nullptr;
        Long        n = 0;
      } impl;
  };

  inline       bytes_ref cut(      bytes_ref b, Long i) { return {b.ptr(i), b.size() - i}; }
  inline const_bytes_ref cut(const_bytes_ref b, Long i) { return {b.ptr(i), b.size() - i}; }
  inline       bytes_ref cut(      bytes_ref b, Long i, Long n) { return {b.ptr(i), min(n, b.size() - i)}; }
  inline const_bytes_ref cut(const_bytes_ref b, Long i, Long n) { return {b.ptr(i), min(n, b.size() - i)}; }
  inline       bytes_ref first_n(      bytes_ref b, Long n) { return cut(b, 0, n); }
  inline const_bytes_ref first_n(const_bytes_ref b, Long n) { return cut(b, 0, n); }
  inline       bytes_ref last_n(      bytes_ref b, Long n) { return cut(b, b.size() - n); }
  inline const_bytes_ref last_n(const_bytes_ref b, Long n) { return cut(b, b.size() - n); }

  template<Long N>
    bytes_ref first_n(byte (&b)[N], Long n) { return first_n(bytes_ref{b}, n); }
  template<Long N>
    const_bytes_ref first_n(const byte (&b)[N], Long n) { return first_n(const_bytes_ref{b}, n); }

  int compare(const_bytes_ref, const_bytes_ref);
  inline bool operator<(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) < 0; }
  inline bool operator<=(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) < 1; }
  inline bool operator>(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) > 0; }
  inline bool operator>=(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) > -1; }
  inline bool operator==(const_bytes_ref a, const_bytes_ref b) { return compare(a, b) == 0; }

  void copy(byte *dst, const_bytes_ref);
  Long copy(bytes_ref dst, const_bytes_ref);

  template<typename T> vector_ref<T> bytes_ref::as_vector() const
  {
    return {(T *)ptr(), size() / (Long)sizeof(T)};
  }

  template<typename T> const_vector_ref<T> const_bytes_ref::as_vector() const
  {
    return {(const T *)ptr(), size() / (Long)sizeof(T)};
  }

}

#endif
