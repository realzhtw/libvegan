#ifndef VEGAN_RUNE_H
#define VEGAN_RUNE_H

namespace vegan {

  enum class rune: int;

  const rune bad_rune = rune{-1};

  inline int ord(rune r) { return (int)r; }

  inline bool operator==(rune a, char b) { return (int)a == b; }
  inline bool operator==(char a, rune b) { return a == (int)b; }

  bool is_white_space(rune);
  bool is_ascii_hex_digit(rune);
  bool is_hex_digit(rune);

}

#endif
