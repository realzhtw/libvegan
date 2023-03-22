#ifndef VEGAN_FILE_PORT_H
#define VEGAN_FILE_PORT_H

#include <vegan/file.h>

namespace vegan {

  class file_port {
    public:
      file_port() {}
      explicit file_port(int fd);
      ~file_port() {}
      virtual void close() { f.close(); }

      Long block_size() const { return bsize; }

    protected:
      file f;
      Long bsize = 0;
  };

}

#endif
