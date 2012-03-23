#ifndef FAS_JSONRPC_METHOD_NOTIFY_HPP
#define FAS_JSONRPC_METHOD_NOTIFY_HPP

#include <fas/jsonrpc/tags.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 

template< typename H, typename V, typename J>
struct notify: type_list_n<
      advice<_notify_, H >,
      definition<_notify_value_, V >,
      definition<_notify_json_, J >
    >::type
{};

  
}}

#endif
