#ifndef FAS_JSONRPC_METHOD_ERROR_HPP
#define FAS_JSONRPC_METHOD_ERROR_HPP

#include <fas/jsonrpc/method/tags.hpp>

#include <fas/jsonrpc/method/ad_send_error.hpp>
#include <fas/jsonrpc/error/json/custom_error.hpp>
#include <fas/jsonrpc/error/json/custom_error_json.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  
template< typename V = custom_error, typename J = custom_error_json >
struct method_error:
  type_list_n<
    advice< _send_error_, ad_send_method_error< V, J > >
  >::type
{};

  
}}

#endif
