if(LIBVEGAN_BUILD_TESTS)
  set(BUILD_GMOCK OFF CACHE BOOL "Disable Google Mock" FORCE)
  add_subdirectory(googletest)
endif()
