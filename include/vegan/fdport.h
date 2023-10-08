#ifndef VEGAN_FDPORT_H
#define VEGAN_FDPORT_H

namespace vegan {

  class fdport {
    public:
      fdport() {}
      explicit fdport(int n, bool autoclose): n{n}, autoclose{autoclose} {}
      fdport(fdport &&);
      fdport(const fdport &) = delete;
      virtual ~fdport() {}

      fdport &operator=(const fdport &) = delete;

      virtual void close();

      int fd() { return n; }

    private:
      int n = -1;
      bool autoclose = false;
  };

}

#endif
