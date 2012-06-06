#ifndef FAS_JSONRPC_OUTGOING_TYPES_REQUEST_OBJECT_HPP
#define FAS_JSONRPC_OUTGOING_TYPES_REQUEST_OBJECT_HPP

#include <fas/jsonrpc/types.hpp>

namespace fas{ namespace jsonrpc{

template<typename V>
struct request_object
{
  typedef const V* request_type;
  request_type params;
  id_t id;
  
  request_object(const V& params, id_t id)
    : params(&params)
    , id(id)
  {}
};

  
}}

#endif
