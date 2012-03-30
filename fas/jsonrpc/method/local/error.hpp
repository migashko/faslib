#ifndef FAS_JSONRPC_METHOD_ERROR_HPP
#define FAS_JSONRPC_METHOD_ERROR_HPP

#include <fas/jsonrpc/method/local/error/tags.hpp>
#include <fas/jsonrpc/method/local/error/ad_invalid_error_id.hpp>
#include <fas/jsonrpc/method/local/error/ad_request_error.hpp>
#include <fas/jsonrpc/method/local/error/ad_request_error_fail.hpp>

#include <fas/jsonrpc/outgoing/types/custom_error.hpp>
#include <fas/jsonrpc/outgoing/json/custom_error_json.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ namespace local{
  
template<
  typename V = custom_error,
  typename J = custom_error_json,
  typename A = empty_list
>
struct error:
  type_list_n<
    A,
    advice< _request_error_, ad_request_error< V, J > >,
    advice< _request_error_fail_, ad_request_error_fail >,
    advice< _invalid_error_id_, ad_invalid_error_id >
  >::type
{};

  
}}}

#endif
