#ifndef VEGAN_IO_BUFFER_H
#define VEGAN_IO_BUFFER_H

#include <vegan/types.h>
#include <vegan/bytes.h>

namespace vegan {

  class io_buffer {
    public:
      io_buffer() {}
      explicit io_buffer(Long n) { resize(n); }

      void resize(Long n);

      Long size() const { return b.size(); }
      Long rdpos() const { return i; }
      Long wrpos() const { return j; }

      byte *rdptr() { return b.ptr(rdpos()); }
      byte *wrptr() { return b.ptr(wrpos()); }

      void advance_rdpos(Long n) { i += n; }
      void backoff_rdpos(Long n) { i -= n; }
      void advance_wrpos(Long n) { j += n; }

      void reset(int keep = 0);

      Long bytes_left() const { return j - i; }
      Long space_left() const { return b.size() - j; }

      const_bytes_ref data() const { return cut(b, i, bytes_left()); }

      bool empty() const { return bytes_left() == 0; }
      bool full() const { return space_left() == 0; }

    private:
      bytes b;
      Long i = 0;
      Long j = 0;
  };

}

#endif
