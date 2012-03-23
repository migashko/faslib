#ifndef FAS_JSONRPC_ASPECT_HPP
#define FAS_JSONRPC_ASPECT_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/error/ad_invalid_request.hpp>
#include <fas/jsonrpc/error/ad_method_not_found.hpp>
#include <fas/jsonrpc/error/ad_not_impl.hpp>
#include <fas/jsonrpc/error/ad_send_error.hpp>
#include <fas/jsonrpc/error/ad_parse_error.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>

#include <fas/serialization/json/ser/serializer.hpp>
#include <fas/serialization/json/deser/deserializer.hpp>
#include <fas/serialization/json/parser/parser.hpp>

#include <fas/adv/ad_container_manager.hpp>

#include <vector>
namespace fas{ namespace jsonrpc{ 

  
  /*
1. Correct JSON (if not => PARSE ERROR) 
2. Correct JSON-RPC (if not => INVALID REQUEST) 
3. Method Match (if not => INVALID METHOD) 
4. Execution 
5. Result (Only for full requests) 
*/

struct default_deserializer: ::fas::json::deser::deserializer<> {};
struct default_serializer: ::fas::json::ser::serializer<> {};
struct default_parser: ::fas::json::parser::parser<> {};
struct default_outgoing_buffer: std::vector<char> {};
struct default_container_manager: ad_container_manager<_outgoing_buffer_> {};

struct error_advice_list:  type_list_n< 
  advice< _invalid_request_, ad_invalid_request >,
  advice< _method_not_found_, ad_method_not_found>,
  advice< _not_impl_, ad_not_impl>, 
  advice< _parse_error_, ad_parse_error>,
  advice< _send_error_, ad_send_error >
>::type {};
  
typedef type_list_n<
  alias<_input_, _jsonrpc_>,
  stub<_jsonrpc_>,
  stub<_output_>,
/*  advice< _invalid_request_, ad_invalid_request >,
  advice< _method_not_found_, ad_method_not_found>,
  advice< _not_impl_, ad_not_impl>, 
  advice< _parse_error_, ad_parse_error>,
  advice< _error_, ad_error >,*/
  advice<_outgoing_buffer_, default_outgoing_buffer >,
  advice<_outgoing_buffer_manager_, default_container_manager >,
  advice<_deserializer_, default_deserializer >,
  advice<_serializer_, default_serializer >,
  advice<_parser_, default_parser >,
  error_advice_list
>::type advice_list;

typedef aspect< advice_list > aspect_type;

struct aspect: aspect_type { };
  
}}

#endif
