#include <vegan/utf8.h>

namespace vegan {
  namespace utf8 {

    int rune_length(rune r)
    {
      auto x = static_cast<int>(r);
      return x <       0x80 ? 1 :
             x <      0x800 ? 2 :
             x <    0x10000 ? 3 :
             x <   0x200000 ? 4 :
             x <  0x4000000 ? 5 :
             x < 0x80000000 ? 6 : 0;
    }

    int encode_rune(rune r, bytes_ref b)
    {
      auto x = static_cast<int>(r);
      if (x < 0x80)  { b[0] = x; return 1; }
      int n = rune_length(r);
      b[0] = x >> (n - 1) * 5 & (1 << 7 - n) - 1;
      for (int i = 1; i != n; ++i)
        b[i] = x >> 6 * i & 0x3f;
      return n;
    }

    int decode_rune_length(byte b)
    {
      return (b >> 7) ==   0 ? 1 :
             (b >> 5) ==   6 ? 2 :
             (b >> 4) ==  14 ? 3 :
             (b >> 3) ==  30 ? 4 :
             (b >> 2) ==  62 ? 5 :
             (b >> 1) == 126 ? 6 : 0;
    }

    rune decode_rune(const byte *p, int n)
    {
      if (n == 0) return bad_rune;
      if (*p < 0x80) return rune{*p};

      int len = decode_rune_length(*p);
      if (n < len) return bad_rune;

      int x = *p & (1 << 7 - n) - 1;
      for (int i = 1; i < len; ++i)
        x = x << 6 | p[i] & 0x3f;
      return rune{x};
    }

  }
}
