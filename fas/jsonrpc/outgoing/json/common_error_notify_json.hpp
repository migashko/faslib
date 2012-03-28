#ifndef FAS_JSONRPC_OUTGOING_JSON_COMMON_ERROR_NOTIFY_JSON_HPP
#define FAS_JSONRPC_OUTGOING_JSON_COMMON_ERROR_NOTIFY_JSON_HPP

#include <fas/jsonrpc/outgoing/json/common_error_code_json.hpp>
#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/meta/null.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ 

namespace aj = ::fas::json;

typedef aj::object<
  type_list_n<
    aj::member< n_jsonrpc, aj::tstring<version> >,
    aj::member< n_error, common_error_code_json >,
    aj::member< n_id, aj::null >
  >::type
> common_error_notify_json;
  
}}

#endif
