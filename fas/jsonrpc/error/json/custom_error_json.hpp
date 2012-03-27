#ifndef FAS_JSONRPC_ERROR_JSON_CUSTOM_ERROR_JSON_HPP
#define FAS_JSONRPC_ERROR_JSON_CUSTOM_ERROR_JSON_HPP

#include <string>

namespace fas{ namespace jsonrpc{ 

typedef aj::object<
  type_list_n<
    aj::member<n_code, aj::attr< custom_error, int, &custom_error::code, aj::integer > >,
    aj::member<n_message, aj::attr< custom_error, std::string, &custom_error::message, aj::string > >
  >::type
> custom_error_json;


}}

#endif
