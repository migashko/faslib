add_executable(
  test_jsonrpc
  
  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp
  test_jsonrpc.cpp
  outgoing_test.cpp
  outgoing_error_test.cpp
  inbound_test.cpp
  common_test.cpp
  method_test.cpp
  error_test.cpp
  invoke_test.cpp
  local_test.cpp
  call_test.cpp 
  handler_test.cpp
)

add_test(jsonrpc test_jsonrpc)



