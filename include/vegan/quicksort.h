#ifndef VEGAN_QUICK_SORT_H
#define VEGAN_QUICK_SORT_H

#include <vegan/types.h>
#include <vegan/utils.h>
#include <vegan/vector_ref.h>
#include <vegan/partition.h>
#include <vegan/stack.h>

namespace vegan {

  template<typename T>
    T median(const T &a, const T &b, const T &c)
    {
      return a < b ? (b < c ? b : max(a, c))
	           : (a < c ? a : max(b, c));
    }

  template<typename T>
    void quicksort(vector_ref<T> v)
    {
      stack<vector_ref<T>> s;
      s.push(v);
      while (!s.empty()) {
	auto x = s.top();
	s.pop();
        if (x.size() < 2) continue;
        if (x.size() == 2) {
          if (!(x[0] < x[1]))
            swap(x[0], x[1]);
          continue;
        }
        auto n = x.size();
        auto m = median(x[0], x[n/2], x[n-1]);
        auto i = partition(x, m);
        if (i <= n/2) {
	  if (n - i > 1) s.push(cut(x, i));
          if (i > 1)     s.push(cut(x, 0, i));
        }
	else {
          if (i > 1)     s.push(cut(x, 0, i));
          if (n - i > 1) s.push(cut(x, i));
	}
      }
    }

  template<typename T, Long n>
    void quicksort(T (&x)[n]) { quicksort(vector_ref<T>{x}); }

}

#endif
