add_subdirectory(benchmark)

add_executable(
  test_range
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
target_link_libraries(test_range PRIVATE fas::testing)

wci_test(NAME range TARGET test_range)





