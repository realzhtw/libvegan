#ifndef VEGAN_TYPE_TRAITS_H
#define VEGAN_TYPE_TRAITS_H

namespace vegan {

  template<typename T> struct make_unsigned {};

  template<> struct make_unsigned<signed char> { using type = unsigned char;      };
  template<> struct make_unsigned<short>       { using type = unsigned short;     };
  template<> struct make_unsigned<int>         { using type = unsigned int;       };
  template<> struct make_unsigned<long>        { using type = unsigned long;      };
  template<> struct make_unsigned<long long>   { using type = unsigned long long; };

  template<typename T> using make_unsigned_t = typename make_unsigned<T>::type;

}

#endif
