#ifndef FAS_SERIALIZATION_JSON_DESER_F_ITEM_DESERIALIZE_HPP
#define FAS_SERIALIZATION_JSON_DESER_F_ITEM_DESERIALIZE_HPP

#include <fas/serialization/json/parser/tags.hpp>

namespace fas{ namespace json{ namespace deser{

template<typename T, typename M>
struct f_item_deserialize
{
  typedef M meta_type;
  typedef typename meta_type::deserializer_tag deserializer_tag;

  T& t;
  
  f_item_deserialize(T& t): t(t){}
  
  template<typename R>
  bool check(R r) const
  {
    return t.get_aspect().template get<deserializer_tag>().check(t, meta_type(), r);
  }
  
  template<typename R>
  R operator()(R r) const
  {
    return t.get_aspect().template get<parser::_value_>()(t, r);
  }
  

  template<typename V, typename R>
  R operator()(V& v, R r) const
  {
    r = t.get_aspect().template get<parser::_space_>()(t, r);
    R current = t.get_aspect().template get<deserializer_tag>()(t, meta_type(), v, r);
    if ( current == r) 
      r = t.get_aspect().template get<parser::_value_>()(t, r);
    else 
      r = current;
    r = t.get_aspect().template get<parser::_space_>()(t, r);
    return r;
    // return t.get_aspect().template get<deserializer_tag>()(t, meta_type(), v, r);
  }
};

}}}

#endif
