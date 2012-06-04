add_executable(
  test_deserializer

  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp
  test_deserializer.cpp

#  number_test.cpp
#  string_test.cpp
#  enumeration_test.cpp
#  sequence_test.cpp
#  field_test.cpp
#  field_list_test.cpp
#  member_test.cpp
#  member_list_test.cpp
#  array_test.cpp
#  raw_test.cpp
  object_test.cpp
  
#  deserializer_test.cpp
)
add_test(json_deserializer test_deserializer)



