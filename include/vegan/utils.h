#ifndef VEGAN_UTILS_H
#define VEGAN_UTILS_H

#include <vegan/types.h>

namespace vegan {

  template<typename T> T min(const T &a, const T &b) { return a < b ? a : b; }
  template<typename T> T max(const T &a, const T &b) { return a < b ? b : a; }

  inline Long abs(Long x) { return x < 0 ? -x : x; }

  template<typename T> void swap(T &a, T &b) { auto x = move(a); a = move(b); b = move(x); }

  template<typename T> Long size(const T &x) { return x.size(); }
  template<typename T> bool empty(const T &x) { return size(x) == 0; }

}

#endif
