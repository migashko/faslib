#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_OBJECT_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_OBJECT_HPP

#include <fas/serialization/common/parser/ad_enclosed_t.hpp>
#include <fas/serialization/common/parser/ad_sequence_t.hpp>
#include <fas/serialization/common/parser/ad_char_t.hpp>
#include <fas/serialization/json/except/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>



#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/expected_of.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/distance.hpp>


namespace fas{ namespace json{ namespace parse{

struct ad_field_sequence:
  ::fas::serialization::parse::ad_sequence_t<_field_, _comma_, _space_, _except_>
{};

struct ad_value_sequence:
  ::fas::serialization::parse::ad_sequence_t<_value_, _comma_, _space_, _except_>
{};

struct ad_comma: 
  ::fas::serialization::parse::ad_char_t<char, ',', _except_>
{};


struct ad_left_brace: 
  ::fas::serialization::parse::ad_char_t<char, '{', _except_>
{};

struct ad_right_brace: 
  ::fas::serialization::parse::ad_char_t<char, '}', _except_>
{};

struct ad_left_bracket: 
  ::fas::serialization::parse::ad_char_t<char, '[', _except_>
{};

struct ad_right_bracket: 
  ::fas::serialization::parse::ad_char_t<char, ']', _except_>
{};

struct ad_object1:
  ::fas::serialization::parse::ad_enclosed_t<_left_brace_, _field_sequence_, _right_brace_, _except_>
{};

struct ad_array1:
  ::fas::serialization::parse::ad_enclosed_t<_left_bracket_, _value_sequence_, _right_bracket_, _except_>
{};


struct aspect_enclosed: aspect< type_list_n<
  advice<_field_sequence_, ad_field_sequence>,
  advice<_value_sequence_, ad_value_sequence>,
  advice<    _left_brace_, ad_left_brace>,
  advice<   _right_brace_, ad_right_brace>, 
  advice<  _left_bracket_, ad_left_bracket>, 
  advice< _right_bracket_, ad_right_bracket>,
  advice<        _object_, ad_object1>,
  advice<         _array_, ad_array1>,
  advice<         _comma_, ad_comma>
>::type >
{};

struct ad_object
{
  
  template<typename T, typename R>
  bool check( T&, R r) {  return r && *r=='{' ; }

  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    if (!r)
      return throw_( t, unexpected_end_fragment(), r );

    if (*r!='{') 
      return throw_( t, expected_of("{",  distance(r) ), r );

    r = t.get_aspect().template get<_space_>()(t, ++r);
    
    if ( !try_(t) )
      return r;
    
    for ( ; r && *r!='}'; )
    {
      r = t.get_aspect().template get<_field_>()(t, r);
      
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
      else if (*r != '}')
        return throw_( t, expected_of("}",  distance(r) ), r );
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
      

    if (*rr.first!='{') 
      return throw_( t, expected_of("{",  distance(rr.first) ), rr.first, rr.second );

    if ( !rr.second )
      return throw_( t, out_of_range( distance(rr.first) ), rr.first, rr.second );
    
    *(rr.second++) = *(rr.first++);
    
    rr = t.get_aspect().template get<_space_>()(t, rr.first, rr.second);
    
    if ( !try_(t) )
      return rr;
    
    for ( ; rr.first && *rr.first!='}'; )
    {
      rr = t.get_aspect().template get<_field_>()(t, rr.first, rr.second);
      
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
        
        if ( !try_(t) )
          return rr;
      }
      else if (*rr.first != '}')
        return throw_( t, expected_of("}",  distance(rr.first) ), rr.first, rr.second );
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
