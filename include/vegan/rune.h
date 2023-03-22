#ifndef VEGAN_RUNE_H
#define VEGAN_RUNE_H

namespace vegan {

  enum class rune: int;

  const rune bad_rune = rune{-1};

  inline bool operator==(rune a, char b) { return (int)a == b; }
  inline bool operator==(char a, rune b) { return a == (int)b; }

  bool isalpha(rune);
  bool isspace(rune);

}

#endif
