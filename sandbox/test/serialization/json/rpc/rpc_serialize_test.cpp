#include <iostream>
#include <fas/serialization/json/rpc/raw_object_json.hpp>
#include <fas/serialization/json/rpc/raw_object.hpp>

#include <fas/serialization/json/deser/deserializer.hpp>

#include <fas/testing.hpp>



/*
#include <fas/serialization/json/parser/ad_space.hpp>
#include <fas/serialization/json/parser/ad_null.hpp>
#include <fas/serialization/json/parser/ad_boolean.hpp>
#include <fas/serialization/json/parser/ad_number.hpp>
#include <fas/serialization/json/parser/ad_string.hpp>
#include <fas/serialization/json/parser/ad_simple_string.hpp>
#include <fas/range.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
*/


UNIT(raw_object_test, "raw_object")
{
  using namespace fas;
  using namespace fas::testing;
  namespace ajr = ::fas::json::rpc;
  
  typedef ::fas::json::deser::deserializer<> deserializer_type;
  
  std::string request = "{}";
  ajr::raw_object robj;
  deserializer_type deser;
  
  deser(ajr::raw_object_json(), robj, (request));
  
  t << is_false<expect>( robj.is_valid() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_request() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_response() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_notify() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_error() ) << FAS_TESTING_FILE_LINE;
  
  request = "{\"jsonrpc\":\"2.0\", \"method\":\"foo\", \"params\": [ 1, 2, 3 ], \"id\":1 }";
  robj = ajr::raw_object();
  deser(ajr::raw_object_json(), robj, (request));
  t << is_true<expect>( robj.is_valid() ) << FAS_TESTING_FILE_LINE;
  t << is_true<expect>( robj.is_request() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_response() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_notify() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_error() ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string("2.0"), std::string(robj.version) ) << robj.version << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string("foo"), std::string(robj.method) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string("[1,2,3]"), std::string(robj.params.begin(), robj.params.end() ) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( 1, robj.id ) << FAS_TESTING_FILE_LINE;
  
  request = "{\"jsonrpc\":\"2.0\", \"result\": [ 1, 2, 3 ], \"id\":1 }";
  robj = ajr::raw_object();
  deser(ajr::raw_object_json(), robj, (request));
  t << is_true <expect>( robj.is_valid() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_request() ) << FAS_TESTING_FILE_LINE;
  t << is_true <expect>( robj.is_response() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_notify() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_error() ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string("2.0"), std::string(robj.version) ) << robj.version << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string(), std::string(robj.method) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string(), std::string(robj.params.begin(), robj.params.end() ) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string("[1,2,3]"), std::string(robj.result.begin(), robj.result.end() ) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( 1, robj.id ) << FAS_TESTING_FILE_LINE;

  request = "{\"jsonrpc\":\"2.0\", \"method\":\"foo\", \"params\": [ 1, 2, 3 ] }";
  robj = ajr::raw_object();
  deser(ajr::raw_object_json(), robj, (request));
  t << is_true<expect>( robj.is_valid() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_request() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_response() ) << FAS_TESTING_FILE_LINE;
  t << is_true<expect>( robj.is_notify() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_error() ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string("2.0"), std::string(robj.version) ) << robj.version << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string("foo"), std::string(robj.method) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string("[1,2,3]"), std::string(robj.params.begin(), robj.params.end() ) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( 0, robj.id ) << FAS_TESTING_FILE_LINE;

  request = "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32600, \"message\": \"Invalid JSON-RPC.\"}, \"id\":null}";
  robj = ajr::raw_object();
  try{
  deser(ajr::raw_object_json(), robj, (request));
  }
  catch(::fas::json::json_error& e)
  {
    std::cout << e.message( (request) ) << std::endl;
  }
  t << is_true<expect>( robj.is_valid() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_request() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_response() ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( robj.is_notify() ) << FAS_TESTING_FILE_LINE;
  t << is_true<expect>( robj.is_error() ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string("2.0"), std::string(robj.version) ) << robj.version << FAS_TESTING_FILE_LINE;
  t << equal<expect>( std::string("{\"code\":-32600,\"message\":\"Invalid JSON-RPC.\"}"), std::string(robj.error.begin(), robj.error.end() ) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( 0, robj.id ) << FAS_TESTING_FILE_LINE;

}



BEGIN_SUITE(rpc_serialize_suite, "basic serialization json-rpc objects suite")
  ADD_UNIT(raw_object_test)
END_SUITE(rpc_serialize_suite)
