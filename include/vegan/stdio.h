#ifndef VEGAN_STDIO_H
#define VEGAN_STDIO_H

#include <vegan/bytes.h>
#include <vegan/rune.h>
#include <vegan/io_error.h>
#include <vegan/vector_ref.h>
#include <vegan/input_port.h>
#include <vegan/output_port.h>

namespace vegan {

  extern input_port &stdin;
  extern output_port &stdout;
  extern output_port &stderr;

  input_port &current_input_port();
  output_port &current_output_port();

  class string;
  class string_ref;

  Long fread(input_port &, byte *, Long);
  bool fread(input_port &, bytes_ref);
  //bool fpeek(input_port &, bytes_ref);
  bool fpeek(input_port &, byte &);
  bool fpeek(input_port &, rune &);
  bool fskip(input_port &, Long n = 1);
  bool fskiprune(input_port &);

  bool fgetbyte(input_port &, byte &);
  bool fgetrune(input_port &, rune &);
  bool fputback(input_port &, byte);
  bool fputback(input_port &, rune);

  string fgetline(input_port &, Long maxlen = 0);

  inline bool peek(rune &c) { return fpeek(stdin, c); }
  inline bool getbyte(byte &b) { return fgetbyte(stdin, b); }
  inline bool getrune(rune &c) { return fgetrune(stdin, c); }

  void fwrite(output_port &, const byte *, Long);
  void fwrite(output_port &, const_bytes_ref);
  void fprint(output_port &, char);
  void fprint(output_port &, rune);
  void fprint(output_port &, int);
  void fprint(output_port &, long);
  void fprint(output_port &, string_ref);
  void fprint(output_port &, const char *);

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
