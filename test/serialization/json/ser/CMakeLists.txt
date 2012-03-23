add_executable(
  test_serializer

  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp
  test_serializer.cpp

  number_test.cpp
  string_test.cpp
  enumeration_test.cpp
  sequence_test.cpp
  field_test.cpp
  field_list_test.cpp
  member_test.cpp
  member_list_test.cpp
  array_test.cpp
  object_test.cpp
  formatting_test.cpp
  raw_test.cpp
  
  
  serializer_test.cpp
)
add_test(json test_serializer)



