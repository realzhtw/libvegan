#ifndef VEGAN_STRING_UTILS_H
#define VEGAN_STRING_UTILS_H

#include <vegan/types.h>
#include <vegan/rune.h>
#include <vegan/string.h>
#include <vegan/vector.h>

namespace vegan {

  bool drop_prefix(string_ref &, string_ref);
  bool drop_suffix(string_ref &, string_ref);

  vector<string_ref> split(string_ref, rune);

}

#endif
