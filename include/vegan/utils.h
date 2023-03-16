#ifndef VEGAN_UTILS_H
#define VEGAN_UTILS_H

#include <vegan/types.h>

namespace vegan {

  template<typename T> T min(const T &a, const T &b) { return a < b ? a : b; }
  template<typename T> T max(const T &a, const T &b) { return a < b ? b : a; }

  inline Long abs(Long x) { return x < 0 ? -x : x; }

  template<typename T> void swap(T &a, T &b) { auto x = a; a = b; b = x; }

}

#endif
