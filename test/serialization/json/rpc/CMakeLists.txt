add_executable(
  test_rpc
  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp
  rpc_serialize_test.cpp
  method_test.cpp
  rpc_test.cpp 
  test_rpc.cpp 
)

add_test(json test_rpc)



