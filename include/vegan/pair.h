#ifndef VEGAN_PAIR_H
#define VEGAN_PAIR_H

#include <vegan/types.h>

namespace vegan {

  template<typename T, typename U> struct pair {
    T first;
    U second;

    pair() {}
    pair(const T &x, const U &y): first{x}, second{y} {}
    pair(T &&x, U &&y): first{move(x)}, second{move(y)} {}
    pair(const pair<T, U> &p): first{p.first}, second{p.second} {}
    pair(pair<T, U> &&p): first{move(p.first)}, second{move(p.second)} {}
  };

  template<typename T, typename U> pair<T, U>
    make_pair(const T &x, const U &y) { return pair<T, U>{x, y}; }

}

#endif
