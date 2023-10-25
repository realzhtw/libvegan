#ifndef VEGAN_PARTITION_H
#define VEGAN_PARTITION_H

#include <vegan/types.h>
#include <vegan/utils.h>
#include <vegan/vector_ref.h>

namespace vegan {

  template<typename T>
    Long partition(vector_ref<T> x, const T &pivot)
    {
      Long i = 0, j = x.size();
      while (i < j) {
	while (i < j && x[i] < pivot)
	  ++i;
	while (i < j && pivot <= x[j-1])
	  --j;
	if (i < j - 1) {
	  swap(x[i], x[j-1]);
	  --j;
	}
      }
      return i;
    }

  template<typename T, Long n>
    Long partition(T (&x)[n], const T &pivot) { return partition(vector_ref{x}, pivot); }

}

#endif
