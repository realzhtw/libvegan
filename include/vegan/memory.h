#ifndef VEGAN_MEMORY_H
#define VEGAN_MEMORY_H

#include <vegan/types.h>
#include <vegan/span.h>

namespace vegan {

  void *alloc(Long n, Long alignment = 1);
  void free(void *);

  template<typename T, typename... Args> void initialize(T *p, Args &&... args);
  template<typename T, typename... Args> void initialize(span<T>, Args &&... args);
  template<typename T> Long initialize(span<T>, span<const T>);
  template<typename T> Long initialize(span<T>, span<T &&>);

  template<typename T> void destroy(T *p) { p->~T(); }
  template<typename T> void destroy(span<T>);

  template<typename T, typename... Args> void initialize(T *p, Args &&... args)
  {
    new (p) T{forward<Args>(args)...};
  }

  template<typename T, typename... Args> void initialize(span<T> x, Args &&...args)
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

  template<typename T> Long initialize(span<T> x, span<const T> y)
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

  template<typename T> Long initialize(span<T> x, rv_span<T> y)
  {
    auto n = min(x.size(), y.size());
    for (Long i = 0; i != n; ++i)
      initialize(x.ptr(i), move(y[i]));
    return n;
  }

  template<typename T> void destroy(span<T> v)
  {
    for (Long i = v.size() - 1; i >= 0; --i)
      destroy(v.ptr(i));
  }

}

template<typename T>
void *operator new(vegan::size_t, T *p) { return p; }

#endif
