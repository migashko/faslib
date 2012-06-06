#ifndef FAS_JSONRPC_METHOD_LOCAL_ERROR_HPP
#define FAS_JSONRPC_METHOD_LOCAL_ERROR_HPP

#include <fas/jsonrpc/method/local/error/ad_invalid_error_id.hpp>
#include <fas/jsonrpc/method/local/error/ad_error_fail.hpp>
#include <fas/jsonrpc/method/local/error/ad_error.hpp>
#include <fas/jsonrpc/method/local/error/tags.hpp>

#include <fas/jsonrpc/outgoing/types/custom_error.hpp>
#include <fas/jsonrpc/outgoing/json/custom_error_json.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ namespace local{

template<
  typename V = custom_error,
  typename J = custom_error_json
>
struct error: ::fas::aspect< 
  typename type_list_n<
    advice< _error_, ad_error< V, J > >,
    advice< _error_fail_, ad_error_fail >,
    advice< _invalid_error_id_, ad_invalid_error_id >
  >::type >
{};

  
}}}

#endif
