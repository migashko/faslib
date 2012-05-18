#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_ITEM_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_ITEM_HPP

#include <fas/serialization/json/except.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/distance.hpp>

namespace fas{ namespace json{ namespace parse{

struct ad_item
{
  template<typename T, typename R>
  bool check(T& t, R r) 
  { 
    return t.get_aspect().template get<_value_>().check(t, r);
  }

  
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    if ( !t.get_aspect().template get<_value_>().check(t, r) )
      return throw_(t, parse_error( distance(r) ), r );
    r = t.get_aspect().template get<_value_>()(t, r);
    r = t.get_aspect().template get<_space_>()(t, r);
    if (!r || *r!=':') return r;
    r = t.get_aspect().template get<_space_>()(t, ++r);
    if (!r) return throw_(t, unexpected_end_fragment( ), r );
    if ( !t.get_aspect().template get<_value_>().check(t, r) )
      return throw_(t, parse_error( distance(r) ), r );
    return t.get_aspect().template get<_value_>()(t, r);

    /*
    if ( t.get_aspect().template get<_null_>().check(r) )
      return t.get_aspect().template get<_null_>()(t, r);

    if ( t.get_aspect().template get<_boolean_>().check(r) )
      return t.get_aspect().template get<_boolean_>()(t, r);

    if ( t.get_aspect().template get<_number_>().check(r) )
      return t.get_aspect().template get<_number_>()(t, r);

    if ( t.get_aspect().template get<_string_>().check(r) )
      return t.get_aspect().template get<_string_>()(t, r);

    if ( t.get_aspect().template get<_array_>().check(r) )
      return t.get_aspect().template get<_array_>()(t, r);

    if ( t.get_aspect().template get<_object_>().check(r) )
      return t.get_aspect().template get<_object_>()(t, r);

    throw parse_error( distance(r) );
    */
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> operator()(T& t, R r, RD rd)
  {
    std::pair<R, RD> rr(r, rd);
    
    if ( !t.get_aspect().template get<_value_>().check(t, rr.first) )
      return throw_(t, parse_error( distance(rr.first) ), rr.first, rr.second );
    
    rr = t.get_aspect().template get<_value_>()(t, rr.first, rr.second);
    rr = t.get_aspect().template get<_space_>()(t, rr.first, rr.second);
    if (!rr.first || *rr.first!=':') return rr;
    
    *(rr.second++) = *(rr.first++);
    
    rr = t.get_aspect().template get<_space_>()(t, rr.first, rr.second);
    if (!rr.first) return throw_(t, unexpected_end_fragment(), rr.first, rr.second );
    
    if ( !t.get_aspect().template get<_value_>().check(t, rr.first) )
      return throw_(t, parse_error( distance(rr.first) ), rr.first, rr.second );
    return t.get_aspect().template get<_value_>()(t, rr.first, rr.second);

    /*
    if ( t.get_aspect().template get<_null_>().check(r) )
      return t.get_aspect().template get<_null_>()(t, r, rd);

    if ( t.get_aspect().template get<_boolean_>().check(r) )
      return t.get_aspect().template get<_boolean_>()(t, r, rd);

    if ( t.get_aspect().template get<_number_>().check(r) )
      return t.get_aspect().template get<_number_>()(t, r, rd);

    if ( t.get_aspect().template get<_string_>().check(r) )
      return t.get_aspect().template get<_string_>()(t, r, rd);

    if ( t.get_aspect().template get<_array_>().check(r) )
      return t.get_aspect().template get<_array_>()(t, r, rd);

    if ( t.get_aspect().template get<_object_>().check(r) )
      return t.get_aspect().template get<_object_>()(t, r, rd);

    throw parse_error( distance(r) );
    */
  }

};

}}}

#endif
