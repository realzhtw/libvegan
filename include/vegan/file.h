#ifndef VEGAN_FILE_H
#define VEGAN_FILE_H

#include <vegan/types.h>
#include <vegan/bytes_ref.h>
#include <vegan/string_ref.h>

namespace vegan {

  class file {
    public:
      file() {}
      explicit file(int fd) { fdopen(fd); }
      ~file();

      void open(string_ref);
      void fdopen(int fd);

      int fd() { return impl.fd; }
      bool is_open() const { return impl.fd != -1; }

      Long read(bytes_ref);
      Long write(const_bytes_ref);
      //void flush();
      Long get_block_size();
      void close();

      file(const file &) = delete;
      file &operator=(const file &) = delete;

    private:
      struct Impl {
        int fd = -1;
        bool autoclose = true;
      } impl;
  };

}

#endif
