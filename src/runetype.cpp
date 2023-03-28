#include <vegan/rune.h>
#include <vegan/bsearch.h>
#include <vegan/vector_ref.h>

namespace {
  using namespace vegan;

  const int _space2[] =
  {
    0x0009, 0x000a, // tab and newline
    0x0020, 0x0020, // space 
    0x00a0, 0x00a0, //
    0x2000, 0x200b, //   - <200b>
    0x2028, 0x2029, //   - 
    0x3000, 0x3000, //
    0xfeff, 0xfeff, // <feff>
  };

  const_vector_ref<int> space2{_space2};

}

namespace vegan {

  bool isspace(rune r)
  {
    auto ss = slice(space2, 0, 2);
    auto pos = bsearch(ss, ord(r));
    return pos < ss.size() && rune{*ss.ptr(pos)} <= r && r <= rune{*(ss.ptr(pos)+1)};
  }
 
}
