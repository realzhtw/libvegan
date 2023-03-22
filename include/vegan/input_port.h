#ifndef VEGAN_INPUT_PORT_H
#define VEGAN_INPUT_PORT_H

#include <vegan/types.h>
#include <vegan/bytes_ref.h>

namespace vegan {

  class input_port {
    public:
      virtual Long read(byte *, Long) = 0;
      Long read(bytes_ref b) { return read(b.ptr(), b.size()); }
      virtual bool unread(const byte *, Long) = 0;
      bool unread(const_bytes_ref b) { return unread(b.ptr(), b.size()); }

      virtual ~input_port() {}
  };

  class unbuffered_input_port: input_port {
    public:
      bool unread(const byte *, Long) override { return false; }
  };

}

#endif
