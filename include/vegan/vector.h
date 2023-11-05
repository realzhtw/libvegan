#ifndef VEGAN_VECTOR_H
#define VEGAN_VECTOR_H

#include <vegan/bytes.h>
#include <vegan/span.h>
#include <vegan/memory.h>
#include <vegan/vector_slice.h>

namespace vegan {

  template<typename T> const T *begin(const vector<T> &x) { return x.ptr(); }
  template<typename T> const T *end(const vector<T> &x) { return x.ptr() + x.size(); }

  template<typename T>
  class vector {
    public:
      vector() {}
      explicit vector(Long n);
      explicit vector(Long n, const T &);
      explicit vector(span<const T> v);
      vector(vector<T> &&v): impl{move(v.impl)} {}
      vector(const vector<T> &v): vector{v.ptr(), v.size()} {}
      ~vector();

            T *ptr(Long i = 0)       { return as_span<      T>(impl).ptr(i); }
      const T *ptr(Long i = 0) const { return as_span<const T>(impl).ptr(i); }

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

  template<typename T> span<T>::span(vector<T> &x): span<T>{x.ptr(), x.size()} {}

  template<typename T>
    vector<T>::vector(Long n): impl{n*(Long)sizeof(T)} { initialize(as_span<T>(impl)); }

  template<typename T>
    vector<T>::vector(Long n, const T &x): impl{n*(Long)sizeof(T)} { initialize(as_span<T>(impl), x); }

  template<typename T>
    vector<T>::vector(span<const T> s): impl{s.size()*(Long)sizeof(T)} { initialize(as_span<T>(impl), s); }

  template<typename T>
    vector<T>::~vector() { destroy(as_span<T>(impl)); }

  template<typename T> vector_slice<T>::vector_slice(vector<T> &v): vector_slice{v.ptr(), 1, v.size()} {}
  template<typename T> const_vector_slice<T>::const_vector_slice(const vector<T> &v): const_vector_slice{v.ptr(), 1, v.size()} {}

}

#endif
