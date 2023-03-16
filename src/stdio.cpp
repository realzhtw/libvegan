#include <vegan/stdio.h>
#include <vegan/file_output_port.h>
#include <vegan/string.h>

namespace vegan {

  file_output_port standard_output_port{1};

  output_port &stdout = standard_output_port;

  void fprint(output_port &op, char c) { op.write(const_bytes_ref((const Byte *)&c, 1)); }

  void fprint(output_port &op, const_string_ref s) { op.write(s.as_bytes()); }

  void fprint(output_port &op, int x) { fprint(op, to_string(x)); }

}
