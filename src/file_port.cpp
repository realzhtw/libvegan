#include <vegan/file_port.h>

namespace vegan {

  file_port::file_port(int fd): f{fd}, bsize{f.get_block_size()} {}

}
