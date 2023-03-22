#include <vegan/io_buffer.h>
#include <vegan/utils.h>

namespace vegan {

  void io_buffer::resize(Long n) { b = bytes{n}; i = j = 0; }

}
