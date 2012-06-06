#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_VALUE_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_VALUE_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/distance.hpp>

#include <iostream>
namespace fas{ namespace json{ namespace parse{

struct ad_value
{
  template<typename T, typename R>
  bool check(T& t, R r) 
  {
    /*
    t.get_aspect().template get<_null_>().check(t, r);
    t.get_aspect().template get<_boolean_>().check(t, r);
    t.get_aspect().template get<_number_>().check(t, r);
    t.get_aspect().template get<_string_>().check(t, r);
    t.get_aspect().template get<_array_>().check(t, r);
    t.get_aspect().template get<_object_>().check(t, r);
    */
    
    return t.get_aspect().template get<_null_>().check(t, r)
           || t.get_aspect().template get<_boolean_>().check(t, r)
           || t.get_aspect().template get<_number_>().check(t, r)
           || t.get_aspect().template get<_string_>().check(t, r)
           || t.get_aspect().template get<_array_>().check(t, r)
           || t.get_aspect().template get<_object_>().check(t, r);

    
  }

  
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    if ( t.get_aspect().template get<_null_>().check(t, r) )
      return t.get_aspect().template get<_null_>()(t, r);
    if ( t.get_aspect().template get<_boolean_>().check(t, r) )
      return t.get_aspect().template get<_boolean_>()(t, r);
    if ( t.get_aspect().template get<_number_>().check(t, r) )
      return t.get_aspect().template get<_number_>()(t, r);
    if ( t.get_aspect().template get<_string_>().check(t, r) )
      return t.get_aspect().template get<_string_>()(t, r);
    if ( t.get_aspect().template get<_array_>().check(t, r) )
      return t.get_aspect().template get<_array_>()(t, r);
    if ( t.get_aspect().template get<_object_>().check(t, r) )
      return t.get_aspect().template get<_object_>()(t, r);
    //throw parse_error( distance(r) );
    return throw_(t, parse_error( distance(r) ), r );
  }

  /*
  template<typename T, typename R, typename RD>
  std::pair<R, RD> operator()(T& t, R r, RD rd)
  {
    if ( t.get_aspect().template get<_null_>().check(t, r) )
      return t.get_aspect().template get<_null_>()(t, r, rd);

    if ( t.get_aspect().template get<_boolean_>().check(t, r) )
      return t.get_aspect().template get<_boolean_>()(t, r, rd);

    if ( t.get_aspect().template get<_number_>().check(t, r) )
      return t.get_aspect().template get<_number_>()(t, r, rd);

    if ( t.get_aspect().template get<_string_>().check(t, r) )
      return t.get_aspect().template get<_string_>()(t, r, rd);

    if ( t.get_aspect().template get<_array_>().check(t, r) )
      return t.get_aspect().template get<_array_>()(t, r, rd);

    if ( t.get_aspect().template get<_object_>().check(t, r) )
      return t.get_aspect().template get<_object_>()(t, r, rd);

    return throw_(t, parse_error( distance(r) ), r, rd );
  }
  */

};

}}}

#endif
