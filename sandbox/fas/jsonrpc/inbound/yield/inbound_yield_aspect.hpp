#ifndef FAS_JSONRPC_INBOUND_YIELD_INBOUND_YIELD_ASPECT_HPP
#define FAS_JSONRPC_INBOUND_YIELD_INBOUND_YIELD_ASPECT_HPP

#include <fas/jsonrpc/inbound/tags.hpp>
#include <fas/jsonrpc/inbound/yeld/yield_parser.hpp>
#include <fas/jsonrpc/inbound/yeld/yield_deserialzier.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{

typedef type_list_n<
  advice< _parser_, yield_parser >,
  advice< _deserialzier_, yield_deserialzier >
>::type inbound_yield_list;

struct inbound_yield_aspect:
  ::fas::aspect < inbound_yield_list >
{

};

}}

#endif

