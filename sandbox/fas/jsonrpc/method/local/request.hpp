#ifndef FAS_JSONRPC_METHOD_LOCAL_REQUEST_HPP
#define FAS_JSONRPC_METHOD_LOCAL_REQUEST_HPP

#include <fas/jsonrpc/method/local/request/ad_parse_request.hpp>
#include <fas/jsonrpc/method/local/request/ad_request_handler.hpp>
#include <fas/jsonrpc/method/local/request/ad_invalid_request_id.hpp>
#include <fas/jsonrpc/method/local/request/ad_request_except.hpp>
#include <fas/jsonrpc/method/local/request/tags.hpp>

#include <fas/jsonrpc/holder.hpp>
#include <fas/jsonrpc/id_manager.hpp>

#include <fas/serialization/json/meta/null.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/value_advice.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ namespace local{

template<
  typename H,
  typename V = empty_type,
  typename J = ::fas::json::null,
  template<typename> class W = holder
>
struct request: ::fas::aspect< 
  typename type_list_n<
    advice< _request_, H >,
    advice< _parse_request_, ad_parse_request< W<V>, J > >,
    advice< _request_handler_, ad_request_handler >,
    advice< _invalid_request_id_, ad_invalid_request_id >,
    advice< _request_except_, ad_request_except >,
    value_advice< _id_, id_manager<> >
  >::type >
{};

  
}}}

#endif
