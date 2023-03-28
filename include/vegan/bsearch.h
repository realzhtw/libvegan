#ifndef VEGAN_BSEARCH_H
#define VEGAN_BSEARCH_H

#include <vegan/vector_slice.h>

namespace vegan {

  template<typename T>
    Long bsearch(const_vector_slice<T> v, const T &x)
    {
      Long a = 0, b = v.size();
      while (a < b) {
        int m = (a + b) / 2;
        if (x <= v[m]) b = m;
        else a = m + 1;
      }
      return a;
    }

  template<typename C, typename T>
    Long bsearch(const C &c, const T &x) { return bsearch(const_vector_slice{c}, x); }

}

#endif
