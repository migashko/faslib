add_executable(copy_range copy_range.cpp)
add_executable(sort_range sort_range.cpp)

if (HAVE_RT_LIB AND FAS_USE_RT_LIB)
  target_link_libraries(copy_range rt)
  target_link_libraries(sort_range rt)
endif (HAVE_RT_LIB AND FAS_USE_RT_LIB)
