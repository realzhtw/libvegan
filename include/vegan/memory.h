#ifndef VEGAN_MEMORY_H
#define VEGAN_MEMORY_H

#include <vegan/types.h>
#include <vegan/vector_ref.h>

namespace vegan {

  template<typename T> void initialize(vector_ref<T>);
  template<typename T> void initialize(vector_ref<T>, const T &);
  template<typename T> void initialize(vector_ref<T>, const_vector_ref<T>);
  template<typename T> void destroy(vector_ref<T>);

  template<typename T> void initialize(vector_ref<T> v)
  {
    for (Long i = 0; i != v.size(); ++i) {
      try {
        new (v.ptr(i)) T{};
      }
      catch(...) {
        destroy(first_n(v, i));
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

  template<typename T> void initialize(vector_ref<T> v, const_vector_ref<T> x)
  {
    for (Long i = 0; i != v.size(); ++i) {
      try {
        new (v.ptr(i)) T{x[i]};
      }
      catch(...) {
        destroy(first_n(v, i));
        throw;
      }
    }
  }

  template<typename T> void destroy(vector_ref<T> v)
  {
    for (Long i = v.size() - 1; i != -1; --i)
      v[i].~T();
  }

}

template<typename T>
void *operator new(vegan::size_t, T *p) { return p; }

#endif
