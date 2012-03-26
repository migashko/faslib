#ifndef FAS_JSONRPC_JSON_SERIALIZER_HPP
#define FAS_JSONRPC_JSON_SERIALIZER_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_merge.hpp>
#include <fas/serialization/json/serializer.hpp>

namespace fas{ namespace jsonrpc{

struct serializer_aspect:
  ::fas::aspect<>
{
};

template<typename A = aspect<> >
struct serializer:
  ::fas::json::serializer< typename aspect_merge<serializer_aspect, A>::type >
{
};

}}

#endif

