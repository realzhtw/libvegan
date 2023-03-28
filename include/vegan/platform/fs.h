#ifndef VEGAN_PLATFORM_FS_H
#define VEGAN_PLATFORM_FS_H

#include <vegan/string_ref.h>

namespace vegan {
  namespace platform {

    struct dir;
 
    dir *opendir(const char *path);
    void closedir(dir *);

    enum class file_type { regular, directory, link, fifo, character_device, block_device, socket, unknown };

    struct direntry {
      string_ref name;
      file_type  type;
    };

    bool readdir(dir *, direntry *);

  }
}

#endif
