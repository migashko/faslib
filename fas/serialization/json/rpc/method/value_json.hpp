#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_VALUE_JSON_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_VALUE_JSON_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect_class.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/typemanip/some_type.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/rpc/response_object.hpp>
#include <fas/serialization/json/rpc/response_object_json.hpp>

#include <string>
#include <iostream>

#include <fas/typemanip/tstring.hpp>
#include <fas/serialization/json/meta/raw.hpp>

namespace fas{ namespace json{ namespace rpc{ namespace method{

/*
template<typename V, typename J>
struct value_json
{
  typedef V value_type;
  typedef J json_type;
  
  template<typename T>
  void clear(T&) 
  {
    _value = value_type();
  }
  
  value_type& value() {return _value;}
  const value_type& value() const {return _value;}
  
  json_type json() const { return json_type();}
  
private:
  value_type _value;
};


FAS_STRING( null_value, "null")

struct null_value_json
  : value_json< tstring<null_value>, raw >
{
};
*/

template<typename V>
struct value
{
  typedef V value_type;
};

template<typename J>
struct json
{
  typedef J json_type;
};


FAS_STRING( null_value, "null")
}}}}

#endif
