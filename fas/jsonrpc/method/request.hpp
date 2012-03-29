#ifndef FAS_JSONRPC_METHOD_REQUEST_HPP
#define FAS_JSONRPC_METHOD_REQUEST_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/method/value_wrapper.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/jsonrpc/method/request/ad_parse_request.hpp>
#include <fas/jsonrpc/method/request/ad_request_handler.hpp>
#include <fas/jsonrpc/method/request/ad_invalid_request_id.hpp>
#include <fas/jsonrpc/method/request/ad_request_except.hpp>
#include <fas/jsonrpc/id_manager.hpp>


#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  

template< typename H, typename V = ::fas::empty_type, typename J = ::fas::json::null, template<typename> class W = value_holder >
struct request: type_list_n<
      advice< _request_, H >,
      advice< _parse_request_, ad_parse_request< W<V>, J > >,
      advice< _request_handler_, ad_request_handler >,
      value_advice< _request_id_, id_manager<> >,
      advice< _invalid_request_id_, ad_invalid_request_id >,
      advice< _request_except_, ad_request_except >
    >::type
{};

  
}}

#endif
