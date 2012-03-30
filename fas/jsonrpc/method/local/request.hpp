#ifndef FAS_JSONRPC_METHOD_REQUEST_HPP
#define FAS_JSONRPC_METHOD_REQUEST_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/holder.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/jsonrpc/method/local/request/ad_parse_request.hpp>
#include <fas/jsonrpc/method/local/request/ad_request_handler.hpp>
#include <fas/jsonrpc/method/local/request/ad_invalid_request_id.hpp>
#include <fas/jsonrpc/method/local/request/ad_request_except.hpp>
#include <fas/jsonrpc/id_manager.hpp>


#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ namespace local{
  

template<
  typename H,
  typename V = empty_type,
  typename J = ::fas::json::null,
  template<typename> class W = holder,
  typename A = empty_list
>
struct request: type_list_n<
      A,
      advice< _request_, H >,
      advice< local::_parse_request_, local::ad_parse_request< W<V>, J > >,
      advice< local::_request_handler_, local::ad_request_handler >,
      value_advice< local::_request_id_, id_manager<> >,
      advice< local::_invalid_request_id_, local::ad_invalid_request_id >,
      advice< local::_request_except_, local::ad_request_except >
    >::type
{};

  
}}}

#endif
