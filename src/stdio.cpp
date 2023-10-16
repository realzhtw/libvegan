#include <vegan/stdio.h>
#include <vegan/file_input_port.h>
#include <vegan/file_output_port.h>
#include <vegan/string.h>
#include <vegan/string_buf.h>
#include <vegan/utf8.h>
#include "platform/io.h"

namespace vegan {

  file_input_port standard_input_port{0, platform::get_block_size(0), false};
  file_output_port standard_output_port{1, platform::get_block_size(1), false};
  file_output_port standard_error_port{2, 0, false};

  input_port &stdin = standard_input_port;
  output_port &stdout = standard_output_port;
  output_port &stderr = standard_error_port;

  stack<input_port *> _input_ports{const_vector_ref<input_port *>{&standard_input_port}};
  stack<output_port *> _output_ports{const_vector_ref<output_port *>{&standard_output_port}};

  Long fread(input_port &ip, byte *p, Long n)
  {
    Long pos = 0;
    while (pos < n) {
      auto r = ip.read_some({p + pos, n - pos});
      if (r == 0) break;
      pos += r;
    }
    return pos;
  }

  bool fpeek(input_port &ip, byte &b)
  {
    if (ip.read_some({&b, 1}) != 1) return false;
    if (!ip.back_off(1)) throw io_error{};
    return true;
  }

  bool fgetrune(input_port &ip, rune &r)
  {
    byte buf[6];
    if (!fpeek(ip, buf[0])) return false;

    int len = utf8::decode_rune_length(buf[0]);
    if (len == 0) return false;

    auto n = fread(ip, buf, len);
    if (n != len) return false;

    r = utf8::decode_rune(buf, n);
    return true;
  }

  bool fputback(input_port &ip, rune r)
  {
    byte buf[6];
    int len = utf8::encode_rune(r, buf);
    if (!ip.back_off(len)) throw io_error{};
    return true;
  }

  bool fpeek(input_port &ip, rune &r)
  {
    if (!fgetrune(ip, r)) return false;
    fputback(ip, r);
    return true;
  }

  string fgetline(input_port &ip, Long maxlen)
  {
    rune r;
    string_buf s;
    while (fgetrune(ip, r) && r != '\n')
      s.append(r);

    return string{s.data()};
  }

  void write(output_port &op, const_bytes_ref b)
  {
    while (b.size() != 0) {
      auto n = write_some(op, b);
      if (n == 0)
        throw io_error{};
      b.drop_first(n);
    }
  }

  void fprint(output_port &op, char c) { write(op, {(const byte *)&c, 1}); }
  void fprint(output_port &op, rune r)
  {
    byte buf[6];
    auto n = utf8::encode_rune(r, buf);
    write(op, first_n(buf, n));
  }
  void fprint(output_port &op, string_ref s) { write(op, s.as_bytes()); }
  void fprint(output_port &op, const char *s) { fprint(op, string_ref{s}); }
  void fprint(output_port &op, int x) { fprint(op, to_string(x)); }
  void fprint(output_port &op, long x) { fprint(op, to_string(x)); }

}
