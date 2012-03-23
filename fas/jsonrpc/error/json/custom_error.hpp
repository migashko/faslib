#ifndef FAS_JSONRPC_ERROR_JSON_CUSTOM_ERROR_HPP
#define FAS_JSONRPC_ERROR_JSON_CUSTOM_ERROR_HPP

#include <string>

namespace fas{ namespace jsonrpc{ 

// for serialize only 
struct custom_error
{
  int id;
  int code;
  std::string message;
  
  custom_error(int code, const std::string& message, int id = -1 )
    : id(id)
    , code(code)
    , message(message)
  {
  }
};


}}

#endif
