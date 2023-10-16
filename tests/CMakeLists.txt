
#find_package(GTest CONFIG REQUIRED)

enable_testing()

include(GoogleTest)

foreach(TEST utf8 output_buffer stdio string string_output_port unique_ptr)
  add_executable(${TEST}_test
    ${TEST}.cpp
  )

  target_link_libraries(${TEST}_test
    vegan
    GTest::gtest_main
  )

  gtest_discover_tests(${TEST}_test)
endforeach()
