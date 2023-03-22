#ifndef VEGAN_TYPES_H
#define VEGAN_TYPES_H

namespace vegan {

  typedef unsigned char byte;

  typedef decltype(sizeof 0) size_t;
  typedef decltype((char *)0 - (char *)0) Long;

  template<typename T> Long size_of(const T &) { return (Long)sizeof(T); }

  template<typename T> struct remove_reference       { typedef T type; };
  template<typename T> struct remove_reference<T &>  { typedef T type; };
  template<typename T> struct remove_reference<T &&> { typedef T type; };
  template<typename T> using remove_reference_t = typename remove_reference<T>::type;

  template<typename T> remove_reference_t<T> &&move(T &&x) noexcept { return static_cast<remove_reference_t<T> &&>(x); }

}

#endif
