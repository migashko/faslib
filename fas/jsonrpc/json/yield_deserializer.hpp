#ifndef FAS_JSONRPC_JSON_YIELD_DESERIALIZER_HPP
#define FAS_JSONRPC_JSON_YIELD_DESERIALIZER_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_merge.hpp>
#include <fas/serialization/json/deserializer.hpp>

namespace fas{ namespace jsonrpc{

struct yield_deserializer_aspect:
  ::fas::aspect<>
{
};

template<typename A = aspect<> >
struct yield_deserializer:
  ::fas::json::deserializer< typename aspect_merge< yield_deserializer_aspect, A>::type >
{
};

}}

#endif

