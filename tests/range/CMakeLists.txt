add_subdirectory(benchmark)

add_executable(
  test_range
  ${FAS_TESTING_CPP}
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
add_test(NAME range-leak COMMAND valgrind --leak-check=full ./test_range)




