#ifndef VEGAN_SORT_H
#define VEGAN_SORT_H

#include <vegan/types.h>
#include <vegan/utils.h>
#include <vegan/vector_ref.h>

namespace vegan {

  struct leo_pair { Long a = 1, b = 1; };

  Long leo_next(Long a, Long b) { return a + b + 1; }
  Long leo_prev(Long a, Long b) { return b - a - 1; }

  void leo_up(leo_pair &L) { L = leo_pair{L.b, L.a + L.b + 1}; }
  void leo_down(leo_pair &L) { L = leo_pair{L.b - L.a - 1, L.a}; }

  void normalize(Long &p, leo_pair &L)
  {
    while ((p & 1) == 0)
      leo_up(L), p >>= 1;
  }

  template<typename T>
  void sift(T *top, leo_pair L)
  {
    while (L.b > 1) {
      T *child = top - (L.b - L.a);
      leo_down(L);
      if (*child < *(top - 1)) {
        child = top - 1;
        leo_down(L);
      }
      if (*child <= *top)
        break;
      swap(*top, *child);
      top = child;
    }
  }

  template<typename T>
  void trinkle(T *top, Long p, leo_pair L)
  {
    while (p > 0) {
      normalize(p, L);
      T *ntop = top - L.b;
      if (p == 1 || *ntop < *top) {
        sift(top, L);
        break;
      }
      --p;
      if (L.b == 1) {
        swap(*ntop, *top);
        top = ntop;
      }
      else {
        T *child = ntop + L.a;
        auto cL = L;
        leo_down(cL);
        if (*child < *(top - 1)) {
          child = top - 1;
          leo_down(cL);
        }
        if (*ntop > *child) {
          swap(*ntop, *top);
          top = ntop;
        }
        else {
          swap(*child, *top);
          sift(child, cL);
          break;
        }
      }
    }
  }

  template<typename T>
  void semitrinkle(T *top, Long p, leo_pair L)
  {
    T *ntop = top - L.b;
    if (p > 1 && *ntop > *top) {
      swap(*ntop, *top);
      trinkle(ntop, p - 1, L);
    }
  }


  template<typename T>
  void smoothsort(T *m, Long n)
  {
    Long p = 1;
    leo_pair L;
    Long i;
    for (i = 1; i < n; ++i) { 
      if ((p & 3) == 3) {
        sift(m + i - 1, L);
        p = (p >> 2) + 1;
        leo_up(L), leo_up(L);
      }
      else {
        if (i + L.a < n)
          sift(m + i - 1, L);
        else
          trinkle(m + i - 1, p, L);
        leo_down(L), p <<= 1;
        while (L.b > 1)
          leo_down(L), p <<= 1;
        ++p;
      }
    }
    trinkle(m + n - 1, p, L);
    while (i > 1) {
      --i;
      if (L.b == 1) {
        --p;
        normalize(p, L);
      }
      else {
        --p;
        leo_down(L), p = (p << 1) + 1;
        semitrinkle(m + (i - L.a) - 1, p, L);
        leo_down(L), p = (p << 1) + 1;
        semitrinkle(m + i - 1, p, L);
      }
    }
  }

  template<typename T>
  void sort(vector_ref<T> x) { return smoothsort(x.ptr(), x.size()); }

  template<typename T>
  void sort(vector<T> &x) { return sort(vector_ref<T>{x}); }
}

#endif
