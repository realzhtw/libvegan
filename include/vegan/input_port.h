#ifndef VEGAN_INPUT_PORT_H
#define VEGAN_INPUT_PORT_H

#include <vegan/types.h>
#include <vegan/bytes_ref.h>

namespace vegan {

  class input_port {
    public:
      virtual Long read_some(bytes_ref) = 0;
      virtual bool unread(const_bytes_ref) = 0;

      virtual ~input_port() {}
  };

}

#endif
