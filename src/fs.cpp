#include <vegan/fs.h>
#include <vegan/vector_buf.h>
#include "platform/fs.h"

namespace {
  using namespace vegan;

  class dir {
    public:
      dir() {}
      explicit dir(platform::dir *p): p{p} {}
      dir(const dir &) = delete;
      ~dir() { close(); }

      dir &operator=(const dir &) = delete;

      platform::dir *ptr() { return p; }

      void close() { if (p) { platform::closedir(p); p = nullptr; } }
    private:
      platform::dir *p = nullptr;
  };

  dir opendir(c_string_ref path);

}

namespace vegan {
  namespace fs {

    vector<string> ls(string_ref path)
    {
      vector_buf<string> r;
      dir d{platform::opendir(string{path}.ptr())};

      platform::direntry e;

      while (platform::readdir(d.ptr(), &e))
        r.append(string{e.name});

      return vector<string>{r.data()};
    }

  }
}
