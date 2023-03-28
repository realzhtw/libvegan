#ifndef VEGAN_STRING_BUF_H
#define VEGAN_STRING_BUF_H

#include <vegan/rune.h>
#include <vegan/bytes.h>
#include <vegan/bytes_ref.h>
#include <vegan/string_ref.h>

namespace vegan {

  class string_buf {
    public:
      string_buf() {}

      string_ref data() const { return first_n(b, i).as_string(); }

      Long size() const { return i; }
      Long capacity() const { return b.size(); }
      void reserve(Long n);

      void append(rune s);
      void append(const_bytes_ref s);
      void append(string_ref s);

    private:
      bytes b;
      Long  i;
  };

}

#endif
