#ifndef FAS_JSONRPC_METHOD_RESULT_HPP
#define FAS_JSONRPC_METHOD_RESULT_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/method/local/result/tags.hpp>
#include <fas/jsonrpc/json/result_object.hpp>
#include <fas/jsonrpc/json/result_object_json.hpp>
#include <fas/jsonrpc/method/local/result/ad_request_result.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ namespace local{
  
template< typename V = const void*, typename J = ::fas::json::null >
struct result: type_list_n<
      advice< _request_result_, ad_request_result< V, J  > >
    >::type
{};

  
}}}

#endif
