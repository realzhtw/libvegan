#ifndef VEGAN_STDIO_H
#define VEGAN_STDIO_H

#include <vegan/bytes.h>
#include <vegan/rune.h>
#include <vegan/io_error.h>
#include <vegan/vector_ref.h>
#include <vegan/stack.h>
#include <vegan/input_port.h>
#include <vegan/output_port.h>

namespace vegan {

  extern input_port &stdin;
  extern output_port &stdout;
  extern output_port &stderr;

  extern stack<input_port *> _input_ports;
  extern stack<output_port *> _output_ports;

  inline input_port &current_input_port() { return *_input_ports.top(); }
  inline output_port &current_output_port() { return *_output_ports.top(); }

  struct current_input_port_guard {
      explicit current_input_port_guard(input_port &p) { _input_ports.push(&p); }
      ~current_input_port_guard() { _input_ports.pop(); }
  };
  struct current_output_port_guard {
      explicit current_output_port_guard(output_port &p) { _output_ports.push(&p); }
      ~current_output_port_guard() { _output_ports.pop(); }
  };

  template<typename F>
    void with_input_from(input_port &p, F &f) { current_input_port_guard g{p}; f(); }

  template<typename F>
    void with_output_to(output_port &p, F &f) { current_output_port_guard g{p}; f(); }

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

  inline bool peek(rune &c) { return fpeek(current_input_port(), c); }
  inline bool getbyte(byte &b) { return fgetbyte(current_input_port(), b); }
  inline bool getrune(rune &c) { return fgetrune(current_input_port(), c); }

  inline Long write_some(output_port &op, const_bytes_ref b) { return op.write_some(b); }
  void write(output_port &, const_bytes_ref);

  inline void fflush(output_port &op) { op.flush(); }
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
      if (x.size() != 0) fprint(op, x[0]);
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

  inline void fprintln(output_port &op) { fprint(op, '\n'); }

  template<typename T, typename... Args>
    void fprintln(output_port &op, const T &x, const Args &... rest) { fprint(op, x); fprintln(op, rest...); }

  template<typename... Args>
    void print(const Args &... args) { fprint(current_output_port(), args...); }

  inline void println() { print('\n'); }

  template<typename T>
    void println(const T &x) { print(x); println(); }

  template<typename T, typename... Args>
    void println(const T &x, const Args &... rest) { print(x); println(rest...); }

}

#endif
