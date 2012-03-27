#ifndef FAS_JSONRPC_JSON_REQUEST_OBJECT_HPP
#define FAS_JSONRPC_JSON_REQUEST_OBJECT_HPP

namespace fas{ namespace jsonrpc{

template<typename V>
struct request_object
{
  typedef const V* params_type;
  params_type params;
  int id;

  request_object(const V& params, int id)
    : params(&params)
    , id(id)
  {}
};

  
}}

#endif
