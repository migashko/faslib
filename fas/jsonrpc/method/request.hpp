#ifndef FAS_JSONRPC_METHOD_REQUEST_HPP
#define FAS_JSONRPC_METHOD_REQUEST_HPP

#include <fas/jsonrpc/tags.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  

template< typename H, typename V = ::fas::empty_type, typename J = ::fas::json::null >
struct request: type_list_n<
      advice<_request_, H >,
      definition<_request_value_, V >,
      definition<_request_json_, J >
    >::type
{};

  
}}

#endif
