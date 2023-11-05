#include <vegan/string_buf.h>
#include <vegan/utils.h>
#include <vegan/utf8.h>

namespace vegan {

  void string_buf::reserve(Long n)
  {
    if (n <= capacity()) return;

    bytes nb{n};

    copy(nb, b);
    b = move(nb);
  }

  void string_buf::append(const_bytes_ref x)
  {
    if (capacity() - size() < x.size())
      reserve(max(capacity() == 0 ? 1 : capacity() * 2, size() + x.size()));

    copy(drop_first(b, i), x);
    i += x.size();
  }

  void string_buf::append(string_ref s) { append(s.as_bytes()); }

  void string_buf::append(rune c)
  {
    byte buf[6];
    int len = utf8::encode_rune(c, buf);
    append(const_bytes_ref{buf, len});
  }

}
