#ifndef FAS_JSONRPC_YIELD_YIELD_DESERIALIZER_HPP
#define FAS_JSONRPC_YIELD_YIELD_DESERIALIZER_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_merge.hpp>
#include <fas/serialization/json/deserializer.hpp>

namespace fas{ namespace jsonrpc{
  
typedef type_list_n<
>::type yield_deserializer_list;
  
struct yield_deserializer_aspect:
  ::fas::aspect< yield_deserializer_list >
{
};

struct yield_deserializer:
  ::fas::json::deserializer< yield_deserializer_aspect >
{
};

}}

#endif

