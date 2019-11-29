add_subdirectory(benchmark)

add_executable(
  test_range
  $ENV{FAS_TESTING_CPP}
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

wci_test(NAME range COMMAND test_range)





