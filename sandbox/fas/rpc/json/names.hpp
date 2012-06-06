#ifndef FAS_RPC_JSON_NAMES_HPP
#define FAS_RPC_JSON_NAMES_HPP

#include <fas/typemanip/tstring.hpp>

namespace fas{ namespace rpc{ namespace json{

FAS_NAME(code)
FAS_NAME(message)
FAS_STRING(s_parse_error, "Parse error.")
FAS_STRING(s_invalid_request, "Invalid Request.")
FAS_STRING(s_method_not_found, "Method not found.")
FAS_STRING(s_invalid_params, "Invalid params.")
FAS_STRING(s_internal_error, "Internal error.")

}}}

#endif
