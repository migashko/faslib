#ifndef FAS_JSONRPC_OUTGOING_TYPES_ERROR_MESSAGE_OBJECT_HPP
#define FAS_JSONRPC_OUTGOING_TYPES_ERROR_MESSAGE_OBJECT_HPP

namespace fas{ namespace jsonrpc{

template<typename V>
struct error_message_object
{
  typedef const V* error_type;
  error_type error;
  int id;
  
  error_message_object(const V& error, int id)
    : error(&error)
    , id(id)
  {}
};

  
}}

#endif
