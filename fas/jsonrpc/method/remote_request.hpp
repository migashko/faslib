#ifndef FAS_JSONRPC_METHOD_REMOTE_REQUEST_HPP
#define FAS_JSONRPC_METHOD_REMOTE_REQUEST_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/json/request_object.hpp>
#include <fas/jsonrpc/json/request_object_json.hpp>
#include <fas/jsonrpc/method/ad_send_request.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  
template< typename V = const void*, typename J = ::fas::json::null >
struct remote_request: type_list_n<
      advice< _send_request_, ad_send_request< V, J, request_object, request_object_json > >,
      advice< _remote_id_, ad_method_id<> >
    >::type
{};

  
}}

#endif
