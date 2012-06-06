#ifndef FAS_JSONRPC_OUTGOING_TYPES_RESULT_OBJECT_HPP
#define FAS_JSONRPC_OUTGOING_TYPES_RESULT_OBJECT_HPP

namespace fas{ namespace jsonrpc{

template<typename V>
struct result_object
{
  typedef const V* result_type;
  result_type result;
  int id;
  
  result_object(const V& result, int id)
    : result(&result)
    , id(id)
  {}
};

  
}}

#endif
