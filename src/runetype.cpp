#include <vegan/rune.h>
#include <vegan/bsearch.h>

namespace {
  using namespace vegan;

  int space2[] =
  {
    0x0009, 0x000a, // tab and newline
    0x0020, 0x0020, // space 
    0x00a0, 0x00a0, //
    0x2000, 0x200b, //   - <200b>
    0x2028, 0x2029, //   - 
    0x3000, 0x3000, //
    0xfeff, 0xfeff, // <feff>
  };

}

namespace vegan {

//  bool isspace(rune r)
//  {
//  }
 
}
