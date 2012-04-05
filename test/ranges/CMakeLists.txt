SUBDIRS(benchmark)

add_executable(
  test_ranges 
  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp
  test_ranges.cpp
  
  basic_test.cpp 
  range_test.cpp 
  array_range_test.cpp 
)

add_test(ranges test_ranges)



