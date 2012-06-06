#ifndef FAS_JSONRPC_METHOD_REMOTE_RESULT_HPP
#define FAS_JSONRPC_METHOD_REMOTE_RESULT_HPP

#include <fas/jsonrpc/method/remote/result/ad_parse_result.hpp>
#include <fas/jsonrpc/method/remote/result/ad_result_handler.hpp>
#include <fas/jsonrpc/method/remote/result/ad_invalid_result.hpp>
#include <fas/jsonrpc/method/remote/result/ad_invalid_result_id.hpp>
#include <fas/jsonrpc/method/remote/result/ad_result_except.hpp>
#include <fas/jsonrpc/method/remote/result/tags.hpp>

#include <fas/jsonrpc/holder.hpp>

#include <fas/serialization/json/meta/null.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/value_advice.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

template<
  typename H,
  typename V = empty_type,
  typename J = ::fas::json::null,
  template<typename> class W = holder
>
struct result: ::fas::aspect< 
  typename type_list_n<
    advice< _result_, H >,
    advice< _parse_result_, ad_parse_result< W<V>, J > >,
    advice< _result_handler_, ad_result_handler >,
    advice< _invalid_result_id_, ad_invalid_result_id >,
    advice< _invalid_result_, ad_invalid_result >,
    advice< _result_except_, ad_result_except >
  >::type >
{};

  
}}}

#endif
