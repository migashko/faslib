#include <fas/jsonrpc/invoke/invoke_aspect.hpp>
#include <fas/jsonrpc/inbound/inbound_aspect.hpp>
#include <fas/jsonrpc/outgoing/outgoing_aspect.hpp>

#include <fas/testing.hpp>

#include <string>
namespace aj = ::fas::json;
namespace ajr = ::fas::jsonrpc;


template<typename T>
inline std::string buffer(T& t)
{
  return t.get_aspect().template get< ajr::_buffer_ >();
}

template<typename T>
inline void clear(T& t)
{
  t.get_aspect().template get< ajr::_buffer_ >().clear();
}

UNIT(invoke, "")
{
  using namespace ::fas::testing;

  
  std::string request_message = "{\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": [42, 23], \"id\": 2}";
  std::string result_message = "{\"jsonrpc\": \"2.0\", \"result\": 19, \"id\": 2}";
  std::string notify_message = "{\"jsonrpc\": \"2.0\", \"method\": \"update\", \"params\": [1,2,3,4,5]}";
  std::string error_message = "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32700, \"message\": \"Parse error.\"}, \"id\": null}";

  std::string method_not_found = "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32601,\"message\":\"Method not found.\"},\"id\":2}";
  std::string method_not_found2 = "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32601,\"message\":\"Method not found.\"},\"id\":null}";

  t.get_aspect().template get< ajr::_inbound_ >()( t, fas::range(request_message) );
  t << equal< expect >( buffer(t), method_not_found ) << FAS_TESTING_FILE_LINE << std::endl << buffer(t) << std::endl << ">>" << method_not_found;
  // clear(t);
  
  t.get_aspect().template get< ajr::_inbound_ >()( t, fas::range(result_message) );
  t << equal< expect >( buffer(t), "" ) << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  // clear(t);
  
  t.get_aspect().template get< ajr::_inbound_ >()( t, fas::range(notify_message) );
  t << equal< expect >( buffer(t), method_not_found2 ) << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  // clear(t);
  
  t.get_aspect().template get< ajr::_inbound_ >()( t, fas::range(error_message) );
  t << equal< expect >( buffer(t), "" ) << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  // clear(t);

  

  
}

BEGIN_SUITE(invoke_suite, "json-rpc invoke suite")
  ADD_UNIT(invoke)
  ADD_ADVICE( ajr::_buffer_, std::string )
  ADD_ASPECT( ajr::invoke_aspect )
  ADD_ASPECT( ajr::inbound_aspect )
  ADD_ASPECT( ajr::outgoing_aspect )
  ADD_STUB( ajr::_output_ )
END_SUITE(invoke_suite)
