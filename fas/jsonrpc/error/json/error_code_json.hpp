#ifndef FAS_JSONRPC_ERROR_JSON_ERROR_CODE_JSON_HPP
#define FAS_JSONRPC_ERROR_JSON_ERROR_CODE_JSON_HPP

#include <fas/jsonrpc/error/error_code.hpp>
#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta/enumeration.hpp>
#include <fas/serialization/json/meta/enum_value.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ 

namespace aj = ::fas::json;

typedef aj::enumeration<
  type_list_n<
    aj::enum_value< s_parse_error,      error_code::parse_error >,
    aj::enum_value< s_invalid_request,  error_code::invalid_request >,
    aj::enum_value< s_method_not_found, error_code::method_not_found >,
    aj::enum_value< s_invalid_params,   error_code::invalid_params >,
    aj::enum_value< s_internal_error,   error_code::internal_error > 
  >::type
> error_code_json;
  
}}

#endif
