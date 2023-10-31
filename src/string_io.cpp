#include <vegan/string_io.h>
#include <vegan/utf8.h>

namespace vegan {

  bool parse_rune(string_ref &s, rune &r)
  {
    if (s.empty()) return false;
    auto &b = s.as_bytes();
    auto n = utf8::decode_rune_length(b[0]);
    if (n > b.size()) return false;
    auto ok = utf8::decode_rune(b, r);
    if (ok) b.drop_first(n);
    return ok;
  }

}
