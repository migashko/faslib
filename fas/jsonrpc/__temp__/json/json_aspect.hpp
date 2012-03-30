#ifndef FAS_JSONRPC_JSON_JSON_ASPECT_HPP
#define FAS_JSONRPC_JSON_JSON_ASPECT_HPP

#include <fas/jsonrpc/json/parser.hpp>
#include <fas/jsonrpc/json/serializer.hpp>
#include <fas/jsonrpc/json/deserializer.hpp>
#include <fas/jsonrpc/json/tags.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{

typedef type_list_n<
  advice< _parser_, parser<> >,
  advice< _serializer_, serializer<> >,
  advice< _deserializer_, deserializer<> >
>::type json_aspect_type_list;

struct json_aspect:
  ::fas::aspect < json_aspect_type_list >
{
  
};

}}

#endif

