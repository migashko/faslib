#ifndef FAS_JSONRPC_JSON_JSON_YIELD_ASPECT_HPP
#define FAS_JSONRPC_JSON_JSON_YIELD_ASPECT_HPP

namespace fas{ namespace jsonrpc{

typedef type_list_n<
  advice< _parser_, yield_parser<> >,
  advice< _serialzier_, serialzier<> >,
  advice< _deserialzier_, yield_deserialzier<> >
>::type json_yield_aspect_type_list;

struct json_yield_aspect:
  ::fas::aspect < json_yield_aspect_type_list >
{

};

}}

#endif

