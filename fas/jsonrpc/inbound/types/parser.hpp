#ifndef FAS_JSONRPC_INBOUND_TYPES_PARSER_HPP
#define FAS_JSONRPC_INBOUND_TYPES_PARSER_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_merge.hpp>

#include <fas/serialization/json/parser.hpp>
#include <fas/serialization/json/except/ad_noexcept.hpp>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
struct parser_aspect:
  ::fas::aspect< advice< aj::_except_, aj::ad_noexcept > >
{
};

template<typename A = ::fas::aspect<> >
struct parser:
  aj::parser< typename aspect_merge< A, parser_aspect>::type >
{
  
};

struct inbound_parser: parser<> {};

}}

#endif
