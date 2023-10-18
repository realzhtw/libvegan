#ifndef VEGAN_MEMORY_H
#define VEGAN_MEMORY_H

#include <vegan/types.h>
#include <vegan/vector_ref.h>

namespace vegan {

  void *alloc(size_t n, size_t alignment = 1);
  void free(void *);

  template<typename T, typename... Args> void initialize(T *p, Args &&... args);
  template<typename T, typename... Args> void initialize(vector_ref<T>, Args &&... args);
  template<typename T> Long initialize(vector_ref<T>, const_vector_ref<T>);
  template<typename T> Long initialize(vector_ref<T>, vector_rv_ref<T>);

  template<typename T> void destroy(T *p) { p->~T(); }
  template<typename T> void destroy(vector_ref<T>);

  template<typename T, typename... Args> void initialize(T *p, Args &&... args)
  {
    new (p) T{forward<Args>(args)...};
  }

  template<typename T, typename... Args> void initialize(vector_ref<T> x, Args &&...args)
  {
    for (Long i = 0; i != x.size(); ++i) {
      try {
        initialize(x.ptr(i), forward<T>(args)...);
      }
      catch(...) {
        destroy(first_n(x, i));
        throw;
      }
    }
  }

  template<typename T> Long initialize(vector_ref<T> x, const_vector_ref<T> y)
  {
    auto n = min(x.size(), y.size());
    for (Long i = 0; i != n; ++i) {
      try {
	initialize(x.ptr(i), y[i]);
      }
      catch(...) {
        destroy(first_n(x, i));
        throw;
      }
    }
    return n;
  }

  template<typename T> Long initialize(vector_ref<T> x, vector_rv_ref<T> y)
  {
    auto n = min(x.size(), y.size());
    for (Long i = 0; i != n; ++i) {
      try {
	initialize(x.ptr(i), move(y[i]));
      }
      catch(...) {
        destroy(vector_ref<T>{x.ptr(), i});
        throw;
      }
    }
    return n;
  }

  template<typename T> void destroy(vector_ref<T> v)
  {
    for (Long i = v.size() - 1; i >= 0; --i)
      destroy(v.ptr(i));
  }

}

template<typename T>
void *operator new(vegan::size_t, T *p) { return p; }

#endif
