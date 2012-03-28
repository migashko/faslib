#ifndef FAS_JSONRPC_OUTGOING_JSON_CUSTOM_ERROR_JSON_HPP
#define FAS_JSONRPC_OUTGOING_JSON_CUSTOM_ERROR_JSON_HPP


#include <fas/jsonrpc/outgoing/types/custom_error.hpp>

#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/integer.hpp>

#include <fas/jsonrpc/names.hpp>

#include <string>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;

typedef aj::object<
  type_list_n<
    aj::member<n_code, aj::attr< custom_error, int, &custom_error::code, aj::integer > >,
    aj::member<n_message, aj::attr< custom_error, std::string, &custom_error::message, aj::string > >
  >::type
> custom_error_json;


}}

#endif
