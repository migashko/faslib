#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_ARRAY_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_ARRAY_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/expected_of.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/distance.hpp>

namespace fas{ namespace json{ namespace parse{

struct ad_array
{
  template<typename R>
  bool check( R r) {  return r && *r=='[' ; }

  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    if (!r)
      return throw_( t, unexpected_end_fragment(), r );

    if (*r!='[') 
      return throw_( t, expected_of("[",  distance(r) ), r );
      

    r = t.get_aspect().template get<_space_>()(t, ++r);
    
    if ( !try_(t) )
      return r;
    
    for ( ; r && *r!=']'; )
    {
      r = t.get_aspect().template get<_value_>()(t, r);
      
      if ( !try_(t) )
        return r;
      
      r = t.get_aspect().template get<_space_>()(t, r);
      
      if ( !try_(t) )
        return r;
      
      if (!r)
        return throw_( t, unexpected_end_fragment(), r );
      
      if (*r == ',')
      {
        ++r;
        r = t.get_aspect().template get<_space_>()(t, r);

        if ( !try_(t) )
          return r;
      }
      else if (*r != ']')
        return throw_( t, expected_of("]",  distance(r) ), r );
        
    }

    if (!r)
      return throw_( t, unexpected_end_fragment(), r );

    return ++r;
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> operator()(T& t, R r, RD rd)
  {
    std::pair<R, RD> rr(r, rd);
    
    if (!rr.first)
      return throw_( t, unexpected_end_fragment(), rr.first, rr.second );

    if (*rr.first!='[') 
      return throw_( t, expected_of("[",  distance(rr.first) ), rr.first, rr.second );
    
    if ( !rr.second )
      return throw_( t, out_of_range( distance(rr.first) ), rr.first, rr.second );
    
    *(rr.second++) = *(rr.first++);
    
    rr = t.get_aspect().template get<_space_>()(t, rr.first, rr.second);
    
    if ( !try_(t) )
      return rr;

    for ( ; rr.first && *rr.first!=']'; )
    {
      rr = t.get_aspect().template get<_value_>()(t, rr.first, rr.second);
      
      if ( !try_(t) )
        return rr;
      
      rr = t.get_aspect().template get<_space_>()(t, rr.first, rr.second);
      
      if ( !try_(t) )
        return rr;
      
      if (!rr.first)
        return throw_( t, unexpected_end_fragment(), rr.first, rr.second );
      
      if (*rr.first == ',')
      {
        if ( !rr.second )
          return throw_( t, out_of_range( distance(rr.first) ), rr.first, rr.second );

        *(rr.second++) = *(rr.first++);

        rr = t.get_aspect().template get<_space_>()(t, rr.first, rr.second);
      }
      else if (*rr.first != ']')
        return throw_( t, expected_of("]",  distance(rr.first) ), rr.first, rr.second );
    }

    if (!rr.first)
      return throw_( t, unexpected_end_fragment(), rr.first, rr.second );

    if ( !rr.second )
      return throw_( t, out_of_range( distance(rr.first) ), rr.first, rr.second );

    *(rr.second++) = *(rr.first++);
    
    return rr;
  }

};

}}}

#endif
