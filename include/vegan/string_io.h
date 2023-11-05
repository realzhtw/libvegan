#ifndef VEGAN_STRING_IO_H
#define VEGAN_STRING_IO_H

#include <vegan/string_ref.h>

namespace vegan {

  bool parse_rune(string_ref &, rune &);

  inline void skip_bytes(string_ref &s, Long n) { s.as_bytes().drop_first(n); }

}

#endif
