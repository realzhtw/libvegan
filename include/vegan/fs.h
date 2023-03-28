#ifndef VEGAN_FS_H
#define VEGAN_FS_H

#include <vegan/vector.h>
#include <vegan/string.h>

namespace vegan {
  namespace fs {

    enum class file_type { regular, directory, link, fifo, character_device, block_device, socket, unknown };

    vector<string> ls(string_ref);

  }
}

#endif
