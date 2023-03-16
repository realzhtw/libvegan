#ifndef VEGAN_STDIO_H
#define VEGAN_STDIO_H

#include <vegan/bytes.h>
#include <vegan/io_error.h>
#include <vegan/string_ref.h>
#include <vegan/vector_ref.h>
//#include <vegan/input_port.h>
#include <vegan/output_port.h>

namespace vegan {

  //extern input_port &stdin;
  extern output_port &stdout;
  //extern output_port &stderr;

  class string;
  class const_string_ref;

  void fprint(output_port &, char);
  void fprint(output_port &, int);
  void fprint(output_port &, const_string_ref);

  template<typename T>
    void fprint(output_port &op, const_vector_ref<T> x)
    {
      fprint(op, '[');
      if (!x.empty()) fprint(op, x[0]);
      for (Long i = 1; i < x.size(); ++i)
        fprint(op, ' ', x[i]);
      fprint(op, ']');
    }

  template<typename T> class vector;
  template<typename T> void fprint(output_port &op, const vector<T> &x) { fprint(op, const_vector_ref<T>{x}); }


  template<typename T, typename U, typename... Args>
    void fprint(output_port &op, const T &x, const U &y, const Args &... rest)
    {
      fprint(op, x);
      fprint(op, y, rest...);
    }

  template<typename... Args>
    void print(const Args &... args) { fprint(stdout, args...); }

  inline void println() { print('\n'); }

  template<typename T>
    void println(const T &x) { print(x); print('\n'); }

  template<typename T, typename... Args>
    void println(const T &x, const Args &... rest) { print(x); println(rest...); }

}

#endif
