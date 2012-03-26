#ifndef FAS_SERIALIZATION_JSON_DESER_AD_OBJECT_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_OBJECT_HPP

#include <fas/serialization/json/except.hpp>
#include <fas/serialization/json/deser/default_space_parser.hpp>
#include <fas/serialization/json/deser/deserialize_array.hpp>
#include <fas/serialization/json/deser/f_item_deserialize.hpp>
#include <fas/range/distance.hpp>

namespace fas{ namespace json{ namespace deser{
  
struct ad_object
{
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r )
  {
    return t.get_aspect().template get<parse::_object_>().is_object(r)
           || t.get_aspect().template get<parse::_null_>().check(r);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    typedef typename M::target target;
    typedef typename target::deserializer_tag deserializer_tag;
    
    
    if ( !r )
      throw unexpected_end_fragment();
    if ( *r != '{' )
      throw expected_of("{", distance(r) );
    if ( !(++r) )
      throw unexpected_end_fragment();
    
    r = t.get_aspect().template get< parse::_space_>()(t, r);
    
    if ( !r )
      throw unexpected_end_fragment();
    
    if ( *r == '}')
      return ++r;
    
    r = t.get_aspect().template get<deserializer_tag>()(t, target(), v, r);
    r = t.get_aspect().template get< parse::_space_>()(t, r);

    if ( *r == '}')
      return ++r;
    
    for ( ;r && *r==',';)
    {
      r = t.get_aspect().template get< parse::_space_>()(t, ++r);
      r = t.get_aspect().template get< parse::_member_>()(t, r);
      r = t.get_aspect().template get< parse::_space_>()(t, r);
    }

    if ( *r!='}' ) 
      throw expected_of("}");

    return ++r;
  }
};

}}}


#endif
