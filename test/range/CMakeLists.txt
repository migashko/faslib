add_subdirectory(benchmark)

add_executable(
  test_range
  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp
  test_range.cpp
  
  basic_suite.cpp 
  basic2_suite.cpp 
  array_range_suite.cpp 
  other_range_suite.cpp
  iterator_range_suite.cpp
  pointer_range_suite.cpp
  container_range_suite.cpp
  stream_range_suite.cpp
  range_suite.cpp
)

add_test(range test_range)



