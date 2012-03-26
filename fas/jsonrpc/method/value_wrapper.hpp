#ifndef FAS_JSONRPC_METHOD_VALUE_WRAPPER_HPP
#define FAS_JSONRPC_METHOD_VALUE_WRAPPER_HPP

#include <fas/typemanip/empty_type.hpp>
#include <fas/range/range.hpp>
namespace fas{ namespace jsonrpc{

template<typename V>
struct value_wrapper
{
  typedef V value_type;
  
  template<typename T>
  value_type operator()(T&)
  {
    return value_type();
  }
};

template<typename V>
struct value_holder
{
  typedef V& value_type;
  
  template<typename T>
  value_type operator()(T&)
  {
    init_range( _value, true );
    return _value;
  }

  V _value;
};

template<>
struct value_holder<empty_type>
  : value_wrapper<empty_type>
  {};

}}

#endif
