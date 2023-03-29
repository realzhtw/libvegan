#include <vegan/stdio.h>

using namespace vegan;

int main()
{
  Long lines = 0;
  Long words = 0;
  Long runes = 0;
  rune r;
  bool word = false;
  while (getrune(r)) {
    if (r == '\n') ++lines;
    bool prev_word = word;
    word = !is_white_space(r);
    if (!prev_word && word) ++words;
    ++runes;
  }
  println("lines: ", lines);
  println("words: ", words);
  println("runes: ", runes);
}
