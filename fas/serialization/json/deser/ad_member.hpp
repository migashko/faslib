#ifndef FAS_SERIALIZATION_JSON_DESER_AD_MEMBER_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_MEMBER_HPP

#include <fas/serialization/json/except.hpp>
#include <fas/serialization/json/deser/default_space_parser.hpp>
#include <fas/serialization/json/deser/deserialize_array.hpp>
#include <fas/serialization/json/deser/f_item_deserialize.hpp>
#include <fas/range/distance.hpp>

namespace fas{ namespace json{ namespace deser{


struct ad_member
{
  template<typename T, typename M, typename R>
  bool check(T& , M, R )
  {
    /*
    return t.get_aspect().template get<parser::_number_>().check(r)
           || t.get_aspect().template get<parser::_null_>().check(r);

    #warning проверить на null member и sequence
    #warning сделать тесты на проверить на null для всех сущностей
    */
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    typedef typename M::target1 target1;
    typedef typename M::target2 target2;
    typedef typename target1::deserializer_tag deserializer_tag1;
    typedef typename target2::deserializer_tag deserializer_tag2;
    R income = r;
    
    if ( !t.get_aspect().template get<deserializer_tag1>().check(t, target1(), r ) )
      return income;

    r = t.get_aspect().template get<deserializer_tag1>()(t, target1(), v, r );
    
    if ( r == income )
      return income;
    r = t.get_aspect().template get< parser::_space_>()(t, r);
    
    if (!r) 
      throw unexpected_end_fragment();
    if ( *r!=':' ) 
      throw expected_of(":", distance(r) );
    
    ++r;
    
    r = t.get_aspect().template get< parser::_space_>()(t, r);
    
    if ( !t.get_aspect().template get<deserializer_tag2>().check(t, target2(), r ) )
      return income;

    R r2 = t.get_aspect().template get<deserializer_tag2>()(t, target2(), v, r );
    
    if (r2==r)
      return income;
    
    return r2;
  }
};



}}}


#endif
