#ifndef VEGAN_UTILS_H
#define VEGAN_UTILS_H

#include <vegan/types.h>

namespace vegan {

  template<typename T, typename U> T min(const T &a, const U &b) { return a < b ? a : b; }
  template<typename T, typename U> T max(const T &a, const U &b) { return a < b ? b : a; }

  inline Long abs(Long x) { return x < 0 ? -x : x; }

  template<typename T> void swap(T &a, T &b) { auto x = move(a); a = move(b); b = move(x); }

  template<typename T> Long size(const T &x) { return x.size(); }

}

#endif
