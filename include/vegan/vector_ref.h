#ifndef VEGAN_VECTOR_REF_H
#define VEGAN_VECTOR_REF_H

#include <vegan/types.h>
#include <vegan/vector_slice.h>

namespace vegan {

  template<typename T> class vector;

  template<typename T> class vector_ref_base {
    public:
      vector_ref_base() {}
      vector_ref_base(T *p, Long n): p{p}, n{n} {}

      T *ptr(Long i = 0) const { return p + i; }
      Long size() const { return n; }

      T &operator[](Long i) const { return *ptr(i); }

      T *begin() const { return this->ptr(); }
      T *end() const { return this->ptr(this->size()); }
    private:
      T    *p = nullptr;
      Long  n = 0;
  };

  template<typename T> class vector_ref: public vector_ref_base<T> {
    public:
      vector_ref() {}
      template<Long n> vector_ref(T (&x)[n]): vector_ref_base<T>{x, n} {}
      vector_ref(T *p, Long n): vector_ref_base<T>{p, n} {}
      vector_ref(const vector_ref<T> &x): vector_ref_base<T>{x.ptr(), x.size()} {}
      vector_ref(vector<T> &);
      explicit vector_ref(T &x): vector_ref_base<T>{&x, 1} {}
  };

  template<typename T> class const_vector_ref: public vector_ref_base<const T> {
    public:
      const_vector_ref() {}
      template<Long n> const_vector_ref(const T (&x)[n]): vector_ref_base<const T>{x, n} {}
      const_vector_ref(const T *p, Long n): vector_ref_base<const T>{p, n} {}
      const_vector_ref(const vector_ref<T> &x): vector_ref_base<const T>{x.ptr(), x.size()} {}
      const_vector_ref(const vector<T> &);
      explicit const_vector_ref(const T &x): vector_ref_base<const T>{&x, 1} {}
  };

  template<typename T> class vector_rv_ref: public vector_ref_base<T> {
    public:
      vector_rv_ref(T *p, Long n): vector_ref_base<T>{p, n} {}
      vector_rv_ref(vector<T> &&v): vector_ref_base<T>{v.ptr(), v.size()} {}
      explicit vector_rv_ref(T &&x): vector_ref_base<T>{&x, 1} {}
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
