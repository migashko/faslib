#ifndef FAS_JSONRPC_OUTGOING_JSON_COMMON_ERROR_MESSAGE_JSON_HPP
#define FAS_JSONRPC_OUTGOING_JSON_COMMON_ERROR_MESSAGE_JSON_HPP

#include <fas/jsonrpc/outgoing/json/common_error_json.hpp>
#include <fas/jsonrpc/outgoing/types/common_error.hpp>

#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/field.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/meta/raw.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ 

namespace aj = ::fas::json;

typedef aj::object<
  type_list_n<
    aj::field<n_jsonrpc, aj::tstring<version> >,
    aj::field<n_error, common_error_json >,
    aj::field<n_id, aj::attr< common_error, int, &common_error::id, aj::integer > >
  >::type
> common_error_message_json;

  
}}

#endif
