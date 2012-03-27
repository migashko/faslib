#ifndef FAS_JSONRPC_ERROR_JSON_ERROR_OBJECT_HPP
#define FAS_JSONRPC_ERROR_JSON_ERROR_OBJECT_HPP

namespace fas{ namespace jsonrpc{

template<typename V>
struct custom_error_object
{
  typedef const V* error_type;
  error_type error;
  int id;
  
  custom_error_object(const V& error, int id)
    : error(&error)
    , id(id)
  {}
};

/*
template<typename V>
struct error_object_notify
{
  typedef const V* result_type;
  result_type result;
  
  error_object_notify(const V& result, int id)
    : result(&result)
    , id(id)
  {}
};
*/

  
}}

#endif
