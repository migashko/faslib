#ifndef FAS_JSONRPC_ASPECT_TYPE_HPP
#define FAS_JSONRPC_ASPECT_TYPE_HPP

#include <fas/jsonrpc/inbound/inbound_aspect.hpp>
#include <fas/jsonrpc/invoke/invoke_aspect.hpp>
//#include <fas/jsonrpc/error/error_aspect.hpp>
//#include <fas/jsonrpc/json/json_aspect.hpp>
#include <fas/jsonrpc/outgoing/outgoing_aspect.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ 

  /*
1. Correct JSON (if not => PARSE ERROR) 
2. Correct JSON-RPC (if not => INVALID REQUEST) 
3. Method Match (if not => INVALID METHOD) 
4. Execution 
5. Result (Only for full requests) 
*/
  
typedef type_list_n<
  inbound_aspect,
  // error_aspect,
  // json_aspect,
  invoke_aspect,
  outgoing_aspect
>::type advice_list;

typedef aspect< advice_list > aspect_type;


  
}}

#endif
