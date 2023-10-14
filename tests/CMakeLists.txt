
find_package(GTest REQUIRED)

enable_testing()

include(GoogleTest)

foreach(TEST utf8 output_buffer)
  add_executable(${TEST}_test
    ${TEST}.cpp
  )

  target_link_libraries(${TEST}_test
    vegan
    GTest::gtest_main
  )

  gtest_discover_tests(${TEST}_test)
endforeach()
