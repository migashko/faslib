#ifndef FAS_JSONRPC_HOLDER_HPP
#define FAS_JSONRPC_HOLDER_HPP

#include <fas/typemanip/empty_type.hpp>
#include <fas/range/range.hpp>


namespace fas{ namespace jsonrpc{

template<typename V>
struct holder
{
  typedef V& value_type;

  template<typename T>
  value_type operator()(T&)
  {
    orange( _value, true );
    return _value;
  }

  V _value;

};

  /*
template<typename V>
struct holder
{
  typedef V value_type;

  template<typename T>
  value_type operator()(T&)
  {
    return value_type();
  }
};

template<typename V>
struct holder<V*>
{
  typedef V* value_type;

  holder(): _value(0) {}
  
  template<typename T>
  value_type operator()(T&)
  {
    return _value;
  }
private:
  value_type _value;
};

template<typename V, int N>
struct holder<V[N]>
{
  typedef V value_type[N];

  template<typename T>
  value_type& operator()(T&)
  {
    return _value;
  }
private:
  value_type _value;
};
*/


  /*
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
struct holder
{
  typedef V& value_type;
  
  template<typename T>
  value_type operator()(T&)
  {
    orange( _value, true );
    return _value;
  }

  V _value;
};

template<>
struct holder<empty_type>
  : value_wrapper<empty_type>
  {};
*/

}}

#endif
