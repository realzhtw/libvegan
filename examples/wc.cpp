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
    //if (isspace(r)) ++words;
    ++runes;
  }
  println("lines = ", lines);
  println("words = ", words);
  println("runes = ", runes);
}
