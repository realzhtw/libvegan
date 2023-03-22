#ifndef VEGAN_INPUT_BUFFER_H
#define VEGAN_INPUT_BUFFER_H

#include <vegan/bytes.h>

namespace vegan {

  class input_buffer {
    public:
      input_buffer() {}
      explicit input_buffer(Long n);

      Long read(bytes_ref);
      Long peek(bytes_ref);
      Long advance(Long);

      bytes_ref room() { return b.last_n(b.size() - bound); }
      void advance_bound(Long n) { bound += n; }

      void resize(Long n) { b = bytes{n}; }

      //Long pos() const { return i; }
      Long bytes_available() const { return bound - i; }
      bool empty() const { return bytes_available() == 0; }

      const_bytes_ref data() const { return b.slice(i, bound - i); }

    private:
      bytes b;
      Long  bound = 0;
      Long  i = 0;
  };

}

#endif
