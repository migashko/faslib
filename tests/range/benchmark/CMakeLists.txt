add_executable(range_benchmark range_benchmark.cpp)

if (HAVE_RT_LIB AND FAS_USE_RT_LIB)
  target_link_libraries(range_benchmark rt)
endif (HAVE_RT_LIB AND FAS_USE_RT_LIB)
