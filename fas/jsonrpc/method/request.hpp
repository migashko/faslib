#ifndef FAS_JSONRPC_METHOD_REQUEST_HPP
#define FAS_JSONRPC_METHOD_REQUEST_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/method/value_wrapper.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/jsonrpc/method/ad_parse_request.hpp>
#include <fas/jsonrpc/method/ad_request_handler.hpp>
#include <fas/jsonrpc/method/ad_method_id.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  

template< typename H, typename V = ::fas::empty_type, typename J = ::fas::json::null, template<typename> class W = value_holder >
struct request: type_list_n<
      advice< _request_, H >,
      advice< _parse_request_, ad_parse_request< W<V>, J > >,
      advice< _request_handler_, ad_request_handler >,
      advice< _method_id_, ad_method_id<> >
    >::type
{};

  
}}

#endif
