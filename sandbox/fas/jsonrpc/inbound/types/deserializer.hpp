#ifndef FAS_JSONRPC_INBOUND_TYPES_DESERIALIZER_HPP
#define FAS_JSONRPC_INBOUND_TYPES_DESERIALIZER_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_merge.hpp>

#include <fas/serialization/json/deserializer.hpp>
#include <fas/serialization/json/except/ad_noexcept.hpp>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
struct deserializer_aspect:
  ::fas::aspect< advice< aj::_except_, aj::ad_noexcept > >
{
};

template<typename A = ::fas::aspect<> >
struct deserializer:
  aj::deserializer< typename aspect_merge< A, deserializer_aspect>::type >
{
  
};

struct inbound_deserializer: deserializer<> {};

}}

#endif
