#include <vegan/stdio.h>

using namespace vegan;

int main()
{
  Long lines = 0;
  Long words = 0;
  Long runes = 0;
  rune r;
  while (getrune(r)) {
    if (r == '\n') ++lines;
    if (is_white_space(r)) ++words;
    ++runes;
  }
  if (!is_white_space(r))
    ++words;
  println("lines: ", lines);
  println("words: ", words);
  println("runes: ", runes);
}
