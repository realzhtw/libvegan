#ifndef VEGAN_MEMORY_H
#define VEGAN_MEMORY_H

#include <vegan/types.h>
#include <vegan/vector_ref.h>

namespace vegan {

  template<typename T> void initialize(vector_ref<T>);
  template<typename T> void initialize(vector_ref<T>, const T &);
  template<typename T> void initialize(T *, const_vector_ref<T>);
  template<typename T> void initialize(T *, vector_rv_ref<T>);
  template<typename T> void destroy(T *, Long n);
  template<typename T> void destroy(vector_ref<T>);

  template<typename T> void initialize(vector_ref<T> x)
  {
    for (Long i = 0; i != x.size(); ++i) {
      try {
        new (x.ptr(i)) T{};
      }
      catch(...) {
        destroy(first_n(x, i));
        throw;
      }
    }
  }

  template<typename T> void initialize(vector_ref<T> v, const T &x)
  {
    for (Long i = 0; i != v.size(); ++i) {
      try {
        new (v.ptr(i)) T{x};
      }
      catch(...) {
        destroy(first_n(v, i));
        throw;
      }
    }
  }

  template<typename T> void initialize(T *p, const_vector_ref<T> x)
  {
    for (Long i = 0; i != x.size(); ++i) {
      try {
        new (p+i) T{x[i]};
      }
      catch(...) {
        destroy(vector_ref<T>{p, i});
        throw;
      }
    }
  }

  template<typename T> void initialize(T *p, vector_rv_ref<T> x)
  {
    for (Long i = 0; i != x.size(); ++i) {
      try {
        new (p+i) T{move(x[i])};
      }
      catch(...) {
        destroy(vector_ref<T>{p, i});
        throw;
      }
    }
  }

  template<typename T> void destroy(T *p, Long n)
  {
    for (Long i = n - 1; i != -1; --i)
      (p+i)->~T();
  }

  template<typename T> void destroy(vector_ref<T> v) { destroy(v.ptr(), v.size()); }

}

template<typename T>
void *operator new(vegan::size_t, T *p) { return p; }

#endif
