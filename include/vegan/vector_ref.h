#ifndef VEGAN_VECTOR_REF_H
#define VEGAN_VECTOR_REF_H

#include <vegan/types.h>

namespace vegan {

  template<typename T> class vector;

  template<typename T> class vector_ref {
    public:
      explicit vector_ref(T *p, Long n): p{p}, n{n} {}
      //vector_ref(vector_ref<T> &x): p{x.p}, n{x.n} {}
      vector_ref(vector<T> &);
      vector_ref(const vector<T> &);
      
      T *ptr(Long i = 0) const { return p + i; }
      Long size() const { return n; }
      bool empty() const { return size() == 0; }

      T &operator[](Long i) const { return *ptr(i); }

      T *begin() const { return p; }
      T *end() const { return p + n; }

    private:
      T    *p;
      Long  n;
  };

  template<typename T> class const_vector_ref {
    public:
      explicit const_vector_ref(const T *p, Long n): p{p}, n{n} {}
      //const_vector_ref(const const_vector_ref<T> &x): p{x.p}, n{x.n} {}
      const_vector_ref(vector_ref<T> x): p{x.ptr()}, n{x.size()} {}
      const_vector_ref(const vector<T> &);
      
      const T *ptr(Long i = 0) const { return p + i; }
      Long size() const { return n; }
      bool empty() const { return size() == 0; }

      const T &operator[](Long i) const { return *ptr(i); }

      const T *begin() const { return p; }
      const T *end() const { return p + n; }

    private:
      const T *p;
      Long     n;
  };

  template<typename T>
    vector_ref<T> cut(vector_ref<T> v, Long i, Long n) { return vector_ref<T>{v.ptr(i), n}; }
  template<typename T>
    const_vector_ref<T> cut(const_vector_ref<T> v, Long i, Long n) { return const_vector_ref<T>{v.ptr(i), n}; }

  template<typename T>
    vector_ref<T> first_n(vector_ref<T> v, Long n) { return cut(v, 0, n); }
  template<typename T>
    const_vector_ref<T> first_n(const_vector_ref<T> v, Long n) { return cut(v, 0, n); }

  template<typename T>
    vector_ref<T> last_n(vector_ref<T> v, Long n) { return cut(v, v.size() - n, n); }
  template<typename T>
    const_vector_ref<T> last_n(const_vector_ref<T> v, Long n) { return cut(v, v.size() - n, n); }

}

#endif
