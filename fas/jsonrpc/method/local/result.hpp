#ifndef FAS_JSONRPC_METHOD_LOCAL_RESULT_HPP
#define FAS_JSONRPC_METHOD_LOCAL_RESULT_HPP


#include <fas/jsonrpc/method/local/result/tags.hpp>
#include <fas/jsonrpc/method/local/result/ad_result.hpp>
#include <fas/jsonrpc/method/local/result/ad_result_fail.hpp>
#include <fas/jsonrpc/method/local/result/ad_invalid_result_id.hpp>

#include <fas/serialization/json/meta/null.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/type_list/type_list_n.hpp>


namespace fas{ namespace jsonrpc{ namespace local{
  
template<
  typename V = empty_type,
  typename J = ::fas::json::null
>
struct result: ::fas::aspect< 
  typename type_list_n<
    advice< _result_, ad_result< V, J  > >,
    advice< _result_fail_, ad_result_fail >,
    advice< _invalid_result_id_, ad_invalid_result_id >
  >::type >
{};
  
}}}

#endif
