#ifndef FAS_JSONRPC_JSON_YIELD_PARSER_HPP
#define FAS_JSONRPC_JSON_YIELD_PARSER_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_merge.hpp>
#include <fas/serialization/json/parser.hpp>

namespace fas{ namespace jsonrpc{

struct yield_parser_aspect:
  ::fas::aspect<>
{
};

template<typename A = aspect<> >
struct yield_parser:
  ::fas::json::parser< typename aspect_merge< yield_parser_aspect, A>::type >
{
};

}}

#endif

