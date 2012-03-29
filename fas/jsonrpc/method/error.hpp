#ifndef FAS_JSONRPC_METHOD_ERROR_HPP
#define FAS_JSONRPC_METHOD_ERROR_HPP

#include <fas/jsonrpc/method/request/tags.hpp>
#include <fas/jsonrpc/method/request/ad_invalid_error_id.hpp>

#include <fas/jsonrpc/method/request/ad_request_error.hpp>
#include <fas/jsonrpc/outgoing/types/custom_error.hpp>
#include <fas/jsonrpc/outgoing/json/custom_error_json.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  
template< typename V = custom_error, typename J = custom_error_json >
struct error:
  type_list_n<
    advice< _request_error_, ad_request_error< V, J > >,
    advice< _invalid_error_id_, ad_invalid_error_id >
  >::type
{};

  
}}

#endif
