#ifndef FAS_JSONRPC_ERROR_CODE_HPP
#define FAS_JSONRPC_ERROR_CODE_HPP

namespace fas{ namespace jsonrpc{ 

/*
-32700   Parse error        Invalid JSON was received by the server. An error occurred on the server while parsing the JSON text.
-32600   Invalid Request    The JSON sent is not a valid Request object.
-32601   Method not found   The method does not exist / is not available.
-32602   Invalid params     Invalid method parameter(s).
-32603   Internal error     Internal JSON-RPC error.
-32000 to -32099  Server error  Reserved for implementation-defined server-errors.

*/
struct error_code
{
  typedef enum
  {
    parse_error = -32700,
    invalid_request = -32600,
    method_not_found = -32601,
    invalid_params = -32602,
    internal_error = -32603   
  } type;
};
  
}}

#endif
