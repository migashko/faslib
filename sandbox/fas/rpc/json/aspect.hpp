#ifndef FAS_RPC_JSON_ASPECT_HPP
#define FAS_RPC_JSON_ASPECT_HPP

#include <fas/rpc/json/tags.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/type_list/type_list_n.hpp>


namespace fas{ namespace rpc{ namespace json{

  /*
1. Correct JSON (if not => PARSE ERROR) 
2. Correct JSON-RPC (if not => INVALID REQUEST) 
3. Method Match (if not => INVALID METHOD) 
4. Execution 
5. Result (Only for full requests) 
*/
  
typedef type_list_n<
>::type advice_list;

typedef aspect< advice_list > aspect_type;

struct aspect: aspect_type { };
  
}}}

#endif
