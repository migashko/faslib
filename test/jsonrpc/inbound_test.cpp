#include <fas/jsonrpc/inbound/inbound_aspect.hpp>
#include <fas/jsonrpc/outgoing/outgoing_aspect.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/testing.hpp>
#include <fas/range.hpp>

namespace aj = ::fas::json;
namespace ajr = ::fas::jsonrpc;

struct ad_invoke_notify
{
  std::string method;
  std::string params;
  
  template<typename T, typename NR, typename PR>
  void operator()( T& t, NR name_range, PR params_range  )
  {
    method.assign( name_range.begin(), name_range.end() );
    params.assign( params_range.begin(), params_range.end() );
  }
};

struct ad_invoke_request
{
  std::string method;
  std::string params;
  int id;
  ad_invoke_request(): id(0) {}
  
  template<typename T, typename NR, typename PR>
  void operator()( T& t, NR name_range, PR params_range, int id  )
  {
    method.assign( name_range.begin(), name_range.end() );
    params.assign( params_range.begin(), params_range.end() );
    this->id = id;
  }
};

struct ad_invoke_result
{
  std::string result;
  int id;
  ad_invoke_result(): id(0) {}
  
  template<typename T, typename RR>
  void operator()( T& t, RR result_range, int id  )
  {
    result.assign( result_range.begin(), result_range.end() );
    this->id = id;
  }
};

struct ad_invoke_error
{
  std::string error;
  int id;
  ad_invoke_error(): id(0) {}
  
  template<typename T, typename RR>
  void operator()( T& t, RR error_range, int id  )
  {
    error.assign( error_range.begin(), error_range.end() );
    this->id = id;
  }
};

UNIT(inbound, "")
{
  using namespace ::fas::testing;
  std::string request_message = "{\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": [42, 23], \"id\": 2}";
  std::string result_message = "{\"jsonrpc\": \"2.0\", \"result\": 19, \"id\": 2}";
  std::string notify_message = "{\"jsonrpc\": \"2.0\", \"method\": \"update\", \"params\": [1,2,3,4,5]}";
  std::string error_message = "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32700, \"message\": \"Parse error.\"}, \"id\": null}";
  
  t.get_aspect().template get< ajr::_inbound_ >()( t, fas::range(request_message) );
  t.get_aspect().template get< ajr::_inbound_ >()( t, fas::range(result_message) );
  t.get_aspect().template get< ajr::_inbound_ >()( t, fas::range(notify_message) );
  t.get_aspect().template get< ajr::_inbound_ >()( t, fas::range(error_message) );
  
  std::string request_method = t.get_aspect().template get< ajr::_invoke_request_ >().method;
  std::string request_params = t.get_aspect().template get< ajr::_invoke_request_ >().params;
  int request_id = t.get_aspect().template get< ajr::_invoke_request_ >().id;
  
  t << equal<expect>( 2, request_id ) << FAS_TESTING_FILE_LINE << std::endl << request_id;
  t << equal<expect, std::string>( request_method, "subtract" ) << FAS_TESTING_FILE_LINE << std::endl << request_method;
  t << equal<expect, std::string>( request_params, "[42,23]" ) << FAS_TESTING_FILE_LINE << std::endl << request_params; 
}


BEGIN_SUITE(inbound_suite, "inbound aspect suite")
  ADD_UNIT(inbound)
  ADD_VALUE_ADVICE( ajr::_buffer_, std::string )
  ADD_STUB( ajr::_output_ )
  ADD_ADVICE( ajr::_invoke_request_, ad_invoke_request )
  ADD_ADVICE( ajr::_invoke_result_, ad_invoke_result )
  ADD_ADVICE( ajr::_invoke_notify_, ad_invoke_notify )
  ADD_ADVICE( ajr::_invoke_error_, ad_invoke_error )
  ADD_ASPECT( ajr::inbound_aspect )
  ADD_ASPECT( ajr::outgoing_aspect )
END_SUITE(inbound_suite)
