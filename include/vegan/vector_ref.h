#ifndef VEGAN_VECTOR_REF_H
#define VEGAN_VECTOR_REF_H

#include <vegan/types.h>
#include <vegan/vector_slice.h>
#include <vegan/utils.h>

namespace vegan {

  template<typename T> class vector;

  template<typename T> class vector_ref_base {
    public:
      vector_ref_base() {}
      vector_ref_base(T *p, Long n): impl{p, n} {}

      T *ptr(Long i = 0) const { return impl.p + i; }
      Long size() const { return impl.n; }

      void drop_first(Long n = 1) { impl.p += n; impl.n -= n; }
      void drop_last(Long n = 1) { impl.n -= n; }

      T &operator[](Long i) const { return *ptr(i); }

      T *begin() const { return this->ptr(); }
      T *end() const { return this->ptr(this->size()); }
    private:
      struct Impl {
        T    *p = nullptr;
        Long  n = 0;
      } impl;
  };

  template<typename T> class vector_rv_ref;

  template<typename T> class vector_ref: public vector_ref_base<T> {
    public:
      vector_ref() {}
      template<Long n> vector_ref(T (&x)[n]): vector_ref_base<T>{x, n} {}
      vector_ref(T *p, Long n): vector_ref_base<T>{p, n} {}
      vector_ref(const vector_ref<T> &x): vector_ref_base<T>{x.ptr(), x.size()} {}
      vector_ref(const vector_rv_ref<T> &);
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

  template<typename T> vector_ref<T>::vector_ref(const vector_rv_ref<T> &x): vector_ref_base<T>{x.ptr(), x.size()} {}

  template<typename T>       vector_ref<T> cut(      vector_ref<T> v, Long i) { return {v.ptr(i), v.size() - i}; }
  template<typename T> const_vector_ref<T> cut(const_vector_ref<T> v, Long i) { return {v.ptr(i), v.size() - i}; }

  template<typename T>       vector_ref<T> cut(      vector_ref<T> v, Long i, Long n) { return {v.ptr(i), min(n, v.size() - i)}; }
  template<typename T> const_vector_ref<T> cut(const_vector_ref<T> v, Long i, Long n) { return {v.ptr(i), min(n, v.size() - i)}; }

  template<typename T>       vector_ref<T> first_n(      vector_ref<T> v, Long n) { return cut(v, 0, n); }
  template<typename T> const_vector_ref<T> first_n(const_vector_ref<T> v, Long n) { return cut(v, 0, n); }

  template<typename T>       vector_ref<T> last_n(      vector_ref<T> v, Long n) { return cut(v, max(v.size() - n, 0)); }
  template<typename T> const_vector_ref<T> last_n(const_vector_ref<T> v, Long n) { return cut(v, max(v.size() - n, 0)); }

  template<typename T> vector_slice<T>::vector_slice(vector_ref<T> x): vector_slice{x.ptr(), 1, x.size()} {}
  template<typename T> const_vector_slice<T>::const_vector_slice(const_vector_ref<T> x): const_vector_slice{x.ptr(), 1, x.size()} {}

  template<typename T>
          vector_slice<T> slice(      vector_ref<T> v, Long i, Long s) { return       vector_slice<T>{v.ptr(i), s, (v.size()-i)/s}; }
  template<typename T>
    const_vector_slice<T> slice(const_vector_ref<T> v, Long i, Long s) { return const_vector_slice<T>{v.ptr(i), s, (v.size()-i)/s}; }

  template<typename T>
    void copy(T *dst, const T *src, Long n) {  while (n-- > 0) *dst++ = *src++; }

  template<typename T>
    void copy(T *dst, const_vector_ref<T> src) { copy(dst, src.ptr(), src.size()); }

  template<typename T>
    bool sorted(const_vector_ref<T> x)
    {
      for (Long i = 0; i < x.size() - 1; ++i)
        if (!(x[i] <= x[i+1]))
          return false;
      return true;
    }

  template<typename T, Long n>
    bool sorted(const T (&x)[n]) { return sorted(const_vector_ref<T>{x}); }

}

#endif
