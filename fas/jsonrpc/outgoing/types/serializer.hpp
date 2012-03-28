#ifndef FAS_JSONRPC_OUTGOING_OUTGOING_SERIALIZER_HPP
#define FAS_JSONRPC_OUTGOING_OUTGOING_SERIALIZER_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_merge.hpp>

#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/except/ad_noexcept.hpp>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
struct serializer_aspect:
  ::fas::aspect< advice< aj::_except_, aj::ad_noexcept > >
{
};

template<typename A = ::fas::aspect<> >
struct serializer:
  aj::serializer< typename aspect_merge< A, serializer_aspect>::type >
{
  
};

struct outgoing_serializer: serializer<> {};


}}

#endif

