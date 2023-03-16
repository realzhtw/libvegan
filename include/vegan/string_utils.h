#ifndef VEGAN_STRING_UTILS_H
#define VEGAN_STRING_UTILS_H

#include <vegan/types.h>
#include <vegan/string.h>
#include <vegan/vector.h>

namespace vegan {

  Long count_chars(string_ref);

  bool has_prefix(string_ref, string_ref);
  bool has_suffix(string_ref, string_ref);

  bool drop_prefix(string_ref &, string_ref);
  bool drop_suffix(string_ref &, string_ref);

  Long find(string_ref, Char);
  Long find(string_ref, string_ref);

  vector<string_ref> split(string_ref, Char);
  vector<string_ref> split(string_ref, string_ref);

}

#endif
