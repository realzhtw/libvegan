

foreach(EXAMPLE sort ls  wc)
  add_executable(${EXAMPLE}
    ${EXAMPLE}.cpp
  )

  target_link_libraries(${EXAMPLE}
    vegan
  )
endforeach()
