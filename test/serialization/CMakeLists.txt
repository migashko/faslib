#SUBDIRS(json benchmark)

add_executable(
  test_ser
  test_ser.cpp
  integer2string_test.cpp
  bool2string_test.cpp
  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp
)
add_test(ser test_ser)

add_subdirectory(json)
#add_subdirectory(benchmark)
