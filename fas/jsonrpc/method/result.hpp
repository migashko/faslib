#ifndef FAS_JSONRPC_METHOD_RESULT_HPP
#define FAS_JSONRPC_METHOD_RESULT_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/method/ad_name.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  
template< typename V, typename J>
struct result: type_list_n<
      definition<_result_value_, V >,
      definition<_result_json_, J >
    >::type
{};

  
}}

#endif
