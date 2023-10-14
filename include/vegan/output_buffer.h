#ifndef VEGAN_OUTPUT_BUFFER_H
#define VEGAN_OUTPUT_BUFFER_H

#include <vegan/bytes.h>
#include <vegan/utils.h>

namespace vegan {

  class output_buffer {
    public:
      explicit output_buffer(Long n = 0): b{n} {}

      const_bytes_ref data() const { return first_n(b, wrpos); }
      byte *wrptr() { return b.ptr(wrpos); }

      Long size() const { return b.size(); }
      Long space_left() const { return size() - wrpos; }
      bool empty() const { return wrpos == 0; }
      bool full() const { return space_left() == 0; }

      void reset() { wrpos = 0; }

      Long write_some(const_bytes_ref src);

    private:
      bytes b;
      Long wrpos = 0;
  };

  inline Long output_buffer::write_some(const_bytes_ref src)
  {
    auto n = min(src.size(), space_left());
    copy(wrptr(), first_n(src, n));
    wrpos += n;
    return n;
  }

}

#endif
