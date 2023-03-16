#ifndef VEGAN_BYTES_REF_H
#define VEGAN_BYTES_REF_H

#include <vegan/types.h>
#include <vegan/vector_ref.h>

namespace vegan {

  class bytes;

  class bytes_ref {
    public:
      bytes_ref() {}
      bytes_ref(bytes &b);
      explicit bytes_ref(Byte *p, Long n): impl{p, n} {}

      Byte *ptr(Long i = 0) const { return impl.p + i; }
      Long size() const { return impl.n; }
      bool empty() const { return size() == 0; }

      Byte &operator[](Long i) const { return *ptr(i); }

      void drop_first(Long n) { impl.p += n; impl.n -= n; }

      bytes_ref first_n(Long n) const { return bytes_ref{ptr(), n}; }
      bytes_ref last_n(Long n) const { return bytes_ref{ptr(size() - n), n}; }

      template<typename T>
        vector_ref<T> as_vector() const {
          return vector_ref<T>{(T *)ptr(), size() / (Long)sizeof(T)};
        }

    private:
      struct Impl {
        Byte *p = nullptr;
        Long  n = 0;
      } impl;
  };

  class const_bytes_ref {
    public:
      const_bytes_ref() {}
      const_bytes_ref(const bytes &b);
      explicit const_bytes_ref(const Byte *p, Long n): impl{p, n} {}
      const_bytes_ref(const bytes_ref &b): impl{b.ptr(), b.size()} {}

      const Byte *ptr(Long i = 0) const { return impl.p + i; }
      Long size() const { return impl.n; }
      bool empty() const { return size() == 0; }

      const Byte &operator[](Long i) const { return *ptr(i); }

      void drop_first(Long n) { impl.p += n; impl.n -= n; }

      const_bytes_ref first_n(Long n) const { return const_bytes_ref{ptr(), n}; }
      const_bytes_ref last_n(Long n) const { return const_bytes_ref{ptr(size() - n), n}; }

      template<typename T>
        const_vector_ref<T> as_vector() const {
          return const_vector_ref<T>{(const T *)ptr(), size() / (Long)sizeof(T)};
        }
 
    private:
      struct Impl {
        const Byte *p = nullptr;
        Long        n = 0;
      } impl;
  };

  inline       bytes_ref cut(      bytes_ref b, Long i, Long n) { return       bytes_ref{b.ptr(i), n}; }
  inline const_bytes_ref cut(const_bytes_ref b, Long i, Long n) { return const_bytes_ref{b.ptr(i), n}; }

}

#endif
