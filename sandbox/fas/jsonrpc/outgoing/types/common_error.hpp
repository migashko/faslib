#ifndef FAS_JSONRPC_OUTGOING_TYPES_COMMON_ERROR_HPP
#define FAS_JSONRPC_OUTGOING_TYPES_COMMON_ERROR_HPP

#include <fas/jsonrpc/error_code.hpp>

namespace fas{ namespace jsonrpc{ 

// for fast serialize only 
struct common_error
{
  int code; // error code
  int id;   // message id
  
  common_error(error_code::type code, int id)
    : code(code)
    , id(id)
  {
  }
};


}}

#endif
