#include <vegan/utf8.h>

namespace vegan {
  namespace utf8 {

    int rune_length(rune r)
    {
      auto x = ord(r);
      return x <       0x80 ? 1 :
             x <      0x800 ? 2 :
             x <    0x10000 ? 3 :
             x <   0x200000 ? 4 :
             x <  0x4000000 ? 5 :
             x < 0x80000000 ? 6 : 0;
    }

    int encode_rune(rune r, bytes_ref b)
    {
      auto x = ord(r);
      if (x < 0x80)  { b[0] = x; return 1; }
      int n = rune_length(r);
      for (auto p = b.ptr(n - 1); p > b.ptr(); --p) {
        *p = 0x80 | (x & 0x3f);
        x >>= 6;
      }
      b[0] = (x & (1 << 7 - n) - 1) | (0xfc << 6 - n);
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

    bool decode_rune(const_bytes_ref b, rune &r)
    {
      if (b.size() == 0) return false;
      if (b[0] < 0x80) { r = rune{b[0]}; return true; }

      int len = decode_rune_length(b[0]);
      if (len > b.size()) return false;

      int x = b[0] & (1 << 7 - len) - 1;
      for (int i = 1; i < len; ++i)
        x = x << 6 | b[i] & 0x3f;
      r = rune{x};
      return true;
    }

  }
}
