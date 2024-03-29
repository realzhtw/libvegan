#ifndef VEGAN_UTF8_H
#define VEGAN_UTF8_H

#include <vegan/rune.h>
#include <vegan/types.h>
#include <vegan/bytes_ref.h>
#include <vegan/exception.h>

namespace vegan {

  class bad_rune: exception {};

  namespace utf8 {

    bool rune_start(byte);

    int rune_length(rune);
    int encode_rune(rune, bytes_ref);

    int decode_rune_length(byte);
    bool decode_rune(const_bytes_ref b, rune &);

  }

}

#endif
