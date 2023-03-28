#ifndef VEGAN_VECTOR_REF_H
#define VEGAN_VECTOR_REF_H

#include <vegan/types.h>
#include <vegan/vector_slice.h>

namespace vegan {

  template<typename T> class vector;

  template<typename T> class vector_ref {
    public:
      vector_ref() {}
      template<Long n> vector_ref(T (&x)[n]): p{x}, n{n} {}
      vector_ref(T *p, Long n): p{p}, n{n} {}
      vector_ref(vector<T> &);
      
      T *ptr(Long i = 0) const { return p + i; }
      Long size() const { return n; }

      T &operator[](Long i) const { return *ptr(i); }

      //vector_slice<T> slice(Long start, Long stride, Long size) const { return 

      T *begin() const { return p; }
      T *end() const { return p + n; }

    private:
      T    *p = nullptr;
      Long  n = 0;
  };

  template<typename T> class const_vector_ref {
    public:
      const_vector_ref() {}
      template<Long n> const_vector_ref(const T (&x)[n]): p{x}, n{n} {}
      const_vector_ref(const T *p, Long n): p{p}, n{n} {}
      const_vector_ref(vector_ref<T> x): p{x.ptr()}, n{x.size()} {}
      const_vector_ref(const vector<T> &);
      
      const T *ptr(Long i = 0) const { return p + i; }
      Long size() const { return n; }

      const T &operator[](Long i) const { return *ptr(i); }

      const T *begin() const { return p; }
      const T *end() const { return p + n; }

    private:
      const T *p = nullptr;
      Long     n = 0;
  };

  template<typename T> class vector_rv_ref {
    public:
      vector_rv_ref(T *p, Long n): p{p}, n{n} {}
      vector_rv_ref(vector<T> &&v): vector_rv_ref{v.ptr(), v.size()} {}

      T *ptr(Long i = 0) const { return p + i; }
      Long size() const { return n; }
      
      T &operator[](Long i) const { return *ptr(i); }

    private:
      T   *p = nullptr;
      Long n = 0;
  };

  template<typename T>
    vector_ref<T> cut(vector_ref<T> v, Long i, Long n) { return {v.ptr(i), n}; }
  template<typename T>
    const_vector_ref<T> cut(const_vector_ref<T> v, Long i, Long n) { return {v.ptr(i), n}; }

  template<typename T>
    vector_ref<T> first_n(vector_ref<T> v, Long n) { return cut(v, 0, n); }
  template<typename T>
    const_vector_ref<T> first_n(const_vector_ref<T> v, Long n) { return cut(v, 0, n); }

  template<typename T>
    vector_ref<T> last_n(vector_ref<T> v, Long n) { return cut(v, v.size() - n, n); }
  template<typename T>
    const_vector_ref<T> last_n(const_vector_ref<T> v, Long n) { return cut(v, v.size() - n, n); }

  template<typename T>
    vector_slice<T>::vector_slice(vector_ref<T> x): vector_slice{x.ptr(), 1, x.size()} {}
  template<typename T>
    const_vector_slice<T>::const_vector_slice(const_vector_ref<T> x): const_vector_slice{x.ptr(), 1, x.size()} {}

  template<typename T>
    vector_slice<T> slice(vector_ref<T> v, Long i, Long s) { return vector_slice<T>{v.ptr(i), s, (v.size()-i)/s}; }
  template<typename T>
    const_vector_slice<T> slice(const_vector_ref<T> v, Long i, Long s) { return const_vector_slice<T>{v.ptr(i), s, (v.size()-i)/s}; }

  template<typename T>
    void copy(T *dst, const T *src, Long n) {  while (n-- > 0) *dst++ = *src++; }

  template<typename T>
    void copy(T *dst, const_vector_ref<T> src) { copy(dst, src.ptr(), src.size()); }

}

#endif
