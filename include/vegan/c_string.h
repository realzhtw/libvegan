#ifndef VEGAN_C_STRING_H
#define VEGAN_C_STRING_H

#include <vegan/types.h>
#include <vegan/bytes_ref.h>

namespace vegan {

  Long c_string_length(const char *);

  Long c_string_copy(bytes_ref, const char *);

}

#endif
