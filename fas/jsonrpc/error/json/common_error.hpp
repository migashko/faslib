#ifndef FAS_JSONRPC_ERROR_JSON_COMMON_ERROR_HPP
#define FAS_JSONRPC_ERROR_JSON_COMMON_ERROR_HPP

#include <fas/jsonrpc/error/error_code.hpp>

namespace fas{ namespace jsonrpc{ 

// for fast serialize only 
struct common_error
{
  int id;
  error_code::type code;
  
  common_error(error_code::type code, int id)
    : id(id)
    , code(code)
  {
  }
};


}}

#endif
