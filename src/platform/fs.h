#ifndef VEGAN_PLATFORM_FS_H
#define VEGAN_PLATFORM_FS_H

#include <vegan/string_ref.h>
#include <vegan/fs.h>

namespace vegan {
  namespace platform {

    struct dir;
 
    dir *opendir(const char *path);
    void closedir(dir *);

    struct direntry {
      string_ref    name;
      fs::file_type type;
    };

    bool readdir(dir *, direntry *);

  }
}

#endif
