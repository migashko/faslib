#ifndef FAS_JSONRPC_INBOUND_YIELD_YIELD_PARSER_HPP
#define FAS_JSONRPC_INBOUND_YIELD_YIELD_PARSER_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_merge.hpp>
#include <fas/serialization/json/parser.hpp>

namespace fas{ namespace jsonrpc{
  
typedef type_list_n<
>::type yield_parser_list;

typedef yield_parser_aspect:
  ::fas::aspect< yield_parser_list >
{
};

struct yield_parser:
  ::fas::json::parser< yield_parser_aspect >
{
};

}}

#endif

