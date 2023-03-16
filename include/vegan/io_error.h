#ifndef VEGAN_IO_ERROR_H
#define VEGAN_IO_ERROR_H

#include <vegan/exception.h>

namespace vegan {

  class io_error: public exception {};

  class write_error: public io_error {};

  class read_error: public io_error {};

}

#endif
