#ifndef VEGAN_VECTOR_H
#define VEGAN_VECTOR_H

#include <vegan/bytes.h>
#include <vegan/vector_ref.h>
#include <vegan/memory.h>

namespace vegan {

  template<typename T> const T *begin(const vector<T> &x) { return x.ptr(); }
  template<typename T> const T *end(const vector<T> &x) { return x.ptr() + x.size(); }

  template<typename T>
  class vector {
    public:
      vector() {}
      explicit vector(Long n);
      explicit vector(Long n, const T &);
      explicit vector(const_vector_ref<T>);
      vector(const vector<T> &x);
      ~vector();

            T *ptr(Long i = 0)       { return impl.as_vector<T>().ptr(i); }
      const T *ptr(Long i = 0) const { return impl.as_vector<T>().ptr(i); }

      Long size() const { return impl.size() / sizeof(T); }
      bool empty() const { return size() == 0; }

      const T &operator[](Long i) const { return *ptr(i); }
            T &operator[](Long i)       { return *ptr(i); }

            T *begin()       { return ptr(); }
      const T *begin() const { return ptr(); }
            T *end()       { return ptr() + size(); }
      const T *end() const { return ptr() + size(); }
    private:
      bytes impl;
  };


  template<typename T>
    vector<T>::vector(Long n): impl{n*(Long)sizeof(T)} { initialize(impl.as_vector<T>()); }

  template<typename T>
    vector<T>::vector(Long n, const T &x): impl{n*sizeof(T)} { initialize(impl.as_vector<T>(), x); }

  template<typename T>
    vector<T>::vector(const_vector_ref<T> v): impl{v.size()*sizeof(T)} { initialize(impl.as_vector<T>(), v); }

  template<typename T>
    vector<T>::~vector() { destroy(impl.as_vector<T>()); impl = bytes{}; }

  template<typename T> vector_ref<T>::vector_ref(vector<T> &v): p{v.ptr()}, n{v.size()} {}

  template<typename T> const_vector_ref<T>::const_vector_ref(const vector<T> &v): p{v.ptr()}, n{v.size()} {}

  template<typename T>
    vector_ref<T> bytes_ref::as_vector() const
    {
      return vector_ref<T>{(T *)ptr(), size() / (Long)sizeof(T)};
    }

  template<typename T>
    const_vector_ref<T> const_bytes_ref::as_vector() const
    {
      return const_vector_ref<T>{(const T *)ptr(), size() / (Long)sizeof(T)};
    }

}

#endif
