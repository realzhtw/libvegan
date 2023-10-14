#ifndef VEGAN_RUNE_H
#define VEGAN_RUNE_H

namespace vegan {

  struct rune {
    int rep = -1;
    rune() {}
    rune(char c): rep{c} {}
    explicit rune(int c): rep{c} {}
  };

  const auto bad_rune = rune{-1};

  inline int ord(rune r) { return r.rep; }

  inline bool operator==(rune a, char b) { return ord(a) == b; }
  inline bool operator!=(rune a, char b) { return !(a == b); }
  inline bool operator==(char a, rune b) { return a == ord(b); }
  inline bool operator!=(char a, rune b) { return !(a == b); }

  bool is_white_space(rune);
  bool is_ascii_hex_digit(rune);
  bool is_hex_digit(rune);

}

#endif
