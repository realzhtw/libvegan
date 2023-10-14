
find_package(GTest REQUIRED)

enable_testing()

include(GoogleTest)

add_executable(utf8_test
  utf8.cpp
)
target_link_libraries(utf8_test
  vegan
  GTest::gtest_main
)

gtest_discover_tests(utf8_test)
