#ifndef FAS_JSONRPC_METHOD_RESULT_HPP
#define FAS_JSONRPC_METHOD_RESULT_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/json/result_object.hpp>
#include <fas/jsonrpc/json/result_object_json.hpp>
#include <fas/jsonrpc/method/request/ad_request_result.hpp>
#include <fas/jsonrpc/method/request/ad_request_result_fail.hpp>
#include <fas/jsonrpc/method/request/ad_invalid_result_id.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  
template< typename V = const void*, typename J = ::fas::json::null >
struct result: type_list_n<
      advice< _send_result_, ad_request_result< V, J /*, result_object, result_object_json*/ > >,
      advice< _request_result_fail_, ad_request_result_fail >,
      advice< _invalid_result_id_, ad_invalid_result_id >
    >::type
{};

  
}}

#endif
