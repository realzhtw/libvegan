
#find_package(GTest CONFIG REQUIRED)

enable_testing()

include(GoogleTest)

foreach(TEST bytes bytes_ref utf8 memory output_buffer holder_ptr partition quicksort sorted span stdio string string_io string_output_port unique_ptr)
  add_executable(${TEST}_test
    ${TEST}.cpp
  )

  target_link_libraries(${TEST}_test
    vegan
    GTest::gtest_main
  )

  gtest_discover_tests(${TEST}_test)
endforeach()
