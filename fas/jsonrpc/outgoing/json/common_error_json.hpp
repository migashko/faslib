#ifndef FAS_JSONRPC_OUTGOING_JSON_COMMON_ERROR_JSON_HPP
#define FAS_JSONRPC_OUTGOING_JSON_COMMON_ERROR_JSON_HPP

#include <fas/jsonrpc/outgoing/json/error_code_json.hpp>
#include <fas/jsonrpc/outgoing/types/common_error.hpp>

#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/attr.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ 

namespace aj = ::fas::json;

typedef aj::object<
  type_list_n<
    aj::member<n_code, aj::attr< common_error, int, &common_error::code, aj::integer > >,
    aj::member<n_message, aj::attr< common_error, int, &common_error::code, error_code_json > >
  >::type
> common_error_json;
  
}}

#endif
