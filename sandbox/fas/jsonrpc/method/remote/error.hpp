#ifndef FAS_JSONRPC_METHOD_REMOTE_ERROR_HPP
#define FAS_JSONRPC_METHOD_REMOTE_ERROR_HPP

#include <fas/jsonrpc/method/remote/error/ad_parse_error.hpp>
#include <fas/jsonrpc/method/remote/error/ad_error_handler.hpp>
#include <fas/jsonrpc/method/remote/error/ad_invalid_error.hpp>
#include <fas/jsonrpc/method/remote/error/ad_invalid_error_id.hpp>
#include <fas/jsonrpc/method/remote/error/ad_error_except.hpp>
#include <fas/jsonrpc/method/remote/error/tags.hpp>

#include <fas/jsonrpc/holder.hpp>

#include <fas/jsonrpc/outgoing/types/custom_error.hpp>
#include <fas/jsonrpc/outgoing/json/custom_error_json.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/value_advice.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

template<
  typename H,
  typename V = custom_error,
  typename J = custom_error_json,
  template<typename> class W = holder
>
struct error: ::fas::aspect< 
  typename type_list_n<
    advice< _error_, H >,
    advice< _parse_error_, ad_parse_error< W<V>, J > >,
    advice< _error_handler_, ad_error_handler >,
    advice< _invalid_error_id_, ad_invalid_error_id >,
    advice< _invalid_error_, ad_invalid_error >,
    advice< _error_except_, ad_error_except >
  >::type >
{};

  
}}}

#endif
