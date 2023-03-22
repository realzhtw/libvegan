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
      Long rd_pos() const { return i; }
      Long wr_pos() const { return j; }

      byte *rd_ptr() { return b.ptr(rd_pos()); }
      byte *wr_ptr() { return b.ptr(wr_pos()); }

      void advance_rdpos(Long n) { i += n; }
      void back_off(Long n)      { i -= n; }
      void advance_wrpos(Long n) { j += n; }

      void reset() { copy(b.ptr(), data()); i = j = 0; }

      Long bytes_left() const { return j - i; }
      Long space_left() const { return b.size() - j; }

      const_bytes_ref data() const { return b.slice(i, bytes_left()); }

      bool empty() const { return bytes_left() == 0; }

    private:
      bytes b;
      Long i = 0;
      Long j = 0;
  };

}

#endif
