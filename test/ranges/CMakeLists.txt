SUBDIRS(benchmark)

add_executable(test_ranges basic_test.cpp range_test.cpp test_ranges.cpp  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp)

add_test(ranges test_ranges)



