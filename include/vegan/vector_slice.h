#ifndef VEGAN_VECTOR_SLICE_H
#define VEGAN_VECTOR_SLICE_H

#include <vegan/types.h>

namespace vegan {

  template<typename T> class vector;
  template<typename T> class span;

  template<typename T>
    class vector_slice {
      public:
        vector_slice() {}
        explicit vector_slice(T *p, Long s, Long n): p{p}, s{s}, n{n} {}
        vector_slice(vector<T> &);
        vector_slice(span<T>);

        T *ptr(Long i = 0) const { return p+i*s; }

        Long size() const { return n; }
        bool empty() const { return size() == 0; }
        T &operator[](Long i) const { return *ptr(i); }

      private:
       T    *p = nullptr;
       Long  s = 0;
       Long  n = 0;
    };

  template<typename T>
    class const_vector_slice {
      public:
        const_vector_slice() {}
        explicit const_vector_slice(const T *p, Long s, Long n): p{p}, s{s}, n{n} {}
        const_vector_slice(const vector<T> &);
        const_vector_slice(span<const T>);

        const T *ptr(Long i = 0) const { return p+i*s; }

        Long size() const { return n; }
        bool empty() const { return size() == 0; }
        const T &operator[](Long i) const { return *ptr(i); }

      private:
       const T *p = nullptr;
       Long     s = 0;
       Long     n = 0;
    };

  template<typename T> vector_slice<T>::vector_slice(span<T> x): vector_slice{x.ptr(), 1, x.size()} {}
  template<typename T> const_vector_slice<T>::const_vector_slice(span<const T> x): const_vector_slice{x.ptr(), 1, x.size()} {}

  template<typename T>
          vector_slice<T> slice(span<      T> v, Long i, Long s) { return       vector_slice<T>{v.ptr(i), s, (v.size()-i)/s}; }
  template<typename T>
    const_vector_slice<T> slice(span<const T> v, Long i, Long s) { return const_vector_slice<T>{v.ptr(i), s, (v.size()-i)/s}; }


}

#endif
