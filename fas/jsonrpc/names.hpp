#ifndef FAS_JSONRPC_NAMES_HPP
#define FAS_JSONRPC_NAMES_HPP

#include <fas/typemanip/tstring.hpp>

namespace fas{ namespace jsonrpc{

FAS_NAME(code)
FAS_NAME(message)
FAS_STRING(s_parse_error, "Parse error.")
FAS_STRING(s_invalid_request, "Invalid Request.")
FAS_STRING(s_method_not_found, "Method not found.")
FAS_STRING(s_invalid_params, "Invalid params.")
FAS_STRING(s_internal_error, "Internal error.")

FAS_NAME(jsonrpc)
FAS_STRING(version, "2.0")
FAS_STRING(null_value, "null")
FAS_NAME(id)
FAS_NAME(method)
FAS_NAME(params)
FAS_NAME(result)
FAS_NAME(error)


}}

#endif
