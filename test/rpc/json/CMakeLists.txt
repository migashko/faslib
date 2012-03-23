add_executable(
  test_jsonrpc
  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp
  test_jsonrpc.cpp 
  
  common_test.cpp
  method_test.cpp
  error_test.cpp
  invoke_test.cpp
  call_test.cpp 
)

add_test(rpc test_jsonrpc)



