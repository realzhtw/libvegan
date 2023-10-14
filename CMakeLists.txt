cmake_minimum_required(VERSION 3.26)

project(libvegan VERSION 1.0 LANGUAGES CXX)

add_library(vegan
  include/vegan/bsearch.h
  include/vegan/bytes.h
  include/vegan/bytes_ref.h
  include/vegan/c_string.h
  include/vegan/exception.h
  include/vegan/fdport.h
  include/vegan/file_input_port.h
  include/vegan/file_output_port.h
  include/vegan/fs.h
  include/vegan/input_port.h
  include/vegan/io_buffer.h
  include/vegan/io_error.h
  include/vegan/memory.h
  include/vegan/output_port.h
  include/vegan/pair.h
  include/vegan/rune.h
  include/vegan/slice.h
  include/vegan/sort.h
  include/vegan/stdio.h
  include/vegan/string.h
  include/vegan/string_buf.h
  include/vegan/string_ref.h
  include/vegan/string_utils.h
  include/vegan/types.h
  include/vegan/utf8.h
  include/vegan/utils.h
  include/vegan/vector.h
  include/vegan/vector_buf.h
  include/vegan/vector_ref.h
  include/vegan/vector_slice.h

  src/bytes.cpp
  src/c_string.cpp
  src/fdport.cpp
  src/file_input_port.cpp
  src/file_output_port.cpp
  src/fs.cpp
  src/input_port.cpp
  src/io_buffer.cpp
  src/output_port.cpp
  src/runetype.cpp
  src/stdio.cpp
  src/string.cpp
  src/string_buf.cpp
  src/to_string.cpp
  src/utf8.cpp

  src/platform/alloc.h
  src/platform/fs.h
  src/platform/io.h
  src/platform/alloc.cpp
  src/platform/fs.cpp
  src/platform/io.cpp
)

target_include_directories(vegan
  PUBLIC
    include
)

add_subdirectory(examples)
add_subdirectory(extern)
add_subdirectory(tests)
