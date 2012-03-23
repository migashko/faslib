#ifndef FAS_JSONRPC_RESPONSE_OBJECT_HPP
#define FAS_JSONRPC_RESPONSE_OBJECT_HPP

/*#include <vector>
#include <algorithm>
#include <fas/range/string_range.hpp>
*/
//#include <fas/range/.hpp>

namespace fas{ namespace jsonrpc{

  /*
template<typename V>
struct result_wrapper
{
  typedef V result_type;
  const result_type& result;
  result_wrapper(const V& result)
    : result(result)
  {}
  
  operator const result_type& () const { return result;}
};
*/
template<typename V>
struct response_object
{
  typedef const V* result_type;
  result_type result;
  int id;
  
  response_object(const V& result, int id)
    : result(&result)
    , id(id)
  {}
};

  
}}

#endif
