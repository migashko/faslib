#ifndef FAS_JSONRPC_ERROR_JSON_ERROR_MESSAGE_JSON_HPP
#define FAS_JSONRPC_ERROR_JSON_ERROR_MESSAGE_JSON_HPP

#include <fas/jsonrpc/error/json/common_error_json.hpp>
#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/meta/raw.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ 

namespace aj = ::fas::json;

typedef aj::object<
  type_list_n<
    aj::member<n_jsonrpc, aj::tstring<version> >,
    aj::member<n_error, common_error_json>,
    aj::member<n_id, aj::attr< common_error, int, &common_error::id, aj::integer > >
  >::type
> error_message_json;

  
}}

#endif
