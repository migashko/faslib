#ifndef FAS_JSONRPC_METHOD_REMOTE_RESULT_HPP
#define FAS_JSONRPC_METHOD_REMOTE_RESULT_HPP

#include <fas/jsonrpc/method/remote/tags.hpp>
#include <fas/jsonrpc/method/value_wrapper.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/jsonrpc/method/remote/ad_parse_response.hpp>
#include <fas/jsonrpc/method/remote/ad_response_handler.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  

template< typename H, typename V = ::fas::empty_type, typename J = ::fas::json::null, template<typename> class W = value_holder >
struct remote_result
  : type_list_n<
      advice< _remote_result_, H >,
      advice< _parse_response_, ad_parse_response< W<V>, J > >,
      advice< _response_handler_, ad_response_handler >
    >::type
{};

  
}}

#endif
