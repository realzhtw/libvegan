#ifndef VEGAN_XML_H
#define VEGAN_XML_H

#include <vegan/types.h>
#include <vegan/rune.h>

namespace vegan {
  namespace xml {

    bool is_name_start_char(rune);
    bool is_name_char(rune);

  }
}

#endif
