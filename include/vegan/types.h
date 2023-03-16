#ifndef VEGAN_TYPES_H
#define VEGAN_TYPES_H

namespace vegan {

  typedef unsigned char Byte;
  typedef int           Char;

  typedef decltype(sizeof 0) size_t;
  typedef decltype((char *)0 - (char *)0) Long;

  template<typename T> Long size_of(const T &) { return (Long)sizeof(T); }

}

#endif
