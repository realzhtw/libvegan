#ifndef VEGAN_OUTPUT_BUFFER_H
#define VEGAN_OUTPUT_BUFFER_H

#include <vegan/types.h>
#include <vegan/bytes.h>

namespace vegan {

  class output_buffer {
    public:
      explicit output_buffer() {}
      explicit output_buffer(Long n): b{n} {}

      Long write(const_bytes_ref);
      void reset() { i = 0; }

      void resize(Long n) { b = bytes{n}; }

      Long pos() const { return i; }
      Long size() const { return b.size(); }
      Long bytes_left() const { return b.size() - i; }
      bool full() const { return bytes_left() == 0; }
      bool empty() const { return pos() == 0; }

      const_bytes_ref data() const { return b.first_n(i); }

    private:
      bytes b;
      Long  i = 0;
  };

}

#endif
