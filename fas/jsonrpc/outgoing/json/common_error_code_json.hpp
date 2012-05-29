#ifndef FAS_JSONRPC_OUTGOING_JSON_COMMON_ERROR_CODE_JSON_HPP
#define FAS_JSONRPC_OUTGOING_JSON_COMMON_ERROR_CODE_JSON_HPP

#include <fas/jsonrpc/outgoing/json/error_code_json.hpp>
#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/field.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ 

namespace aj = ::fas::json;

typedef aj::object<
  type_list_n<
    aj::field<n_code, aj::integer >,
    aj::field<n_message, error_code_json >
  >::type
> common_error_code_json;

  
}}

#endif
