#ifndef FAS_JSONRPC_METHOD_RESULT_HPP
#define FAS_JSONRPC_METHOD_RESULT_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/json/result_object.hpp>
#include <fas/jsonrpc/json/result_object_json.hpp>
#include <fas/jsonrpc/method/ad_send_result.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  
template< typename V = const void*, typename J = ::fas::json::null >
struct result: type_list_n<
      advice< _send_result_, ad_send_result< V, J, result_object, result_object_json > >
    >::type
{};

  
}}

#endif
