#include <vegan/rune.h>
#include <vegan/bsearch.h>
#include <vegan/span.h>

namespace {
  using namespace vegan;

  const int white_space_tbl[] = {
    0x0009, 0x000d, // Cc   [5] <control-0009>..<control-000D>
    0x0020, 0x0020, // Zs       SPACE
    0x0085, 0x0085, // Cc       <control-0085>
    0x00a0, 0x00a0, // Zs       NO-BREAK SPACE
    0x1680, 0x1680, // Zs       OGHAM SPACE MARK
    0x2000, 0x200a, // Zs  [11] EN QUAD..HAIR SPACE
    0x2028, 0x2028, // Zl       LINE SEPARATOR
    0x2029, 0x2029, // Zp       PARAGRAPH SEPARATOR
    0x202f, 0x202f, // Zs       NARROW NO-BREAK SPACE
    0x205f, 0x205f, // Zs       MEDIUM MATHEMATICAL SPACE
    0x3000, 0x3000  // Zs       IDEOGRAPHIC SPACE
  };

  const int hex_digit_tbl[] = {
    0x0030, 0x0039, // Nd  [10] DIGIT ZERO..DIGIT NINE
    0x0041, 0x0046, // L&   [6] LATIN CAPITAL LETTER A..LATIN CAPITAL LETTER F
    0x0061, 0x0066, // L&   [6] LATIN SMALL LETTER A..LATIN SMALL LETTER F
    0xff10, 0xff19, // Nd  [10] FULLWIDTH DIGIT ZERO..FULLWIDTH DIGIT NINE
    0xff21, 0xff26, // L&   [6] FULLWIDTH LATIN CAPITAL LETTER A..FULLWIDTH LATIN CAPITAL LETTER F
    0xff41, 0xff46, // L&   [6] FULLWIDTH LATIN SMALL LETTER A..FULLWIDTH LATIN SMALL LETTER F
  };

  const int ascii_hex_digit_tbl[] = {
    0x0030, 0x0039, // Nd  [10] DIGIT ZERO..DIGIT NINE
    0x0041, 0x0046, // L&   [6] LATIN CAPITAL LETTER A..LATIN CAPITAL LETTER F
    0x0061, 0x0066, // L&   [6] LATIN SMALL LETTER A..LATIN SMALL LETTER F
  };

}


namespace vegan {

  bool has_property(rune r, const_span<int> tbl)
  {
    auto x = ord(r);
    auto i = bsearch(tbl, x);
    return i < tbl.size() && (tbl[i] == x || (i & 1));
  }

  bool is_white_space(rune r)     { return has_property(r, white_space_tbl); }
  bool is_ascii_hex_digit(rune r) { return has_property(r, ascii_hex_digit_tbl); }
  bool is_hex_digit(rune r)       { return has_property(r, hex_digit_tbl); }
 
}
