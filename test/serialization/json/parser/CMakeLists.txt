add_executable(
  test_parser 
  test_parser.cpp 
  common_test.cpp 
  object_test.cpp 
  parser_test.cpp 
  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp
)

add_test(json test_parser)



