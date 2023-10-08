#include <vegan/fdport.h>
#include "platform/io.h"

namespace vegan {

  void fdport::close()
  {
    platform::close(fd());
  }

}
