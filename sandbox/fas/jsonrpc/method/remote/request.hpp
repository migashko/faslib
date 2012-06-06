#ifndef FAS_JSONRPC_METHOD_REMOTE_REQUEST_HPP
#define FAS_JSONRPC_METHOD_REMOTE_REQUEST_HPP


#include <fas/jsonrpc/method/remote/request/tags.hpp>
#include <fas/jsonrpc/method/remote/request/ad_request.hpp>
#include <fas/jsonrpc/method/remote/request/ad_request_fail.hpp>
#include <fas/jsonrpc/method/remote/request/ad_invalid_request_id.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/jsonrpc/id_manager.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/type_list/type_list_n.hpp>


namespace fas{ namespace jsonrpc{ namespace remote{
  
template<
  typename V = empty_type,
  typename J = ::fas::json::null
>
struct request: ::fas::aspect< 
  typename type_list_n<
    advice< _request_, ad_request< V, J  > >,
    advice< _request_fail_, ad_request_fail >,
    advice< _invalid_request_id_, ad_invalid_request_id >,
    value_advice< _id_, id_manager<> >
  >::type >
{};
  
}}}

#endif
