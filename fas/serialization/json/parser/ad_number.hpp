#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_NUMBER_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_NUMBER_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/invalid_json_number.hpp>
#include <fas/serialization/json/except/expected_of.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/except/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/distance.hpp>

namespace fas{ namespace json{ namespace parse{

struct ad_number
{

  template<typename T, typename R>
  bool check( T&, R r) {  return r && ( *r=='-' || ( *r>='0' && *r<='9' ) ); }

  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    return this->parse(t, r);
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> operator()(T& t, R r, RD rd)
  {
    return this->copy(t, r, rd);
  }

private:
  
  template<typename T, typename R>
  R parse_digit(T& t, R r)
  {
    for ( ;r && *r >= '0' && *r <= '9'; ++r);
    return r;
  }

  template<typename T, typename R, typename RD>
  R copy_digit(T& t, R r, RD& rd)
  {
    for ( ;r && *r >= '0' && *r <= '9'; ++r, ++rd )
    {
      if ( !rd ) 
        return throw_( t, out_of_range(distance(r)), r );
      *rd = *r;
    }
    return r;
  }

  template<typename T, typename R>
  R parse(T& t, R r)
  {
    if ( r && *r=='-')
      ++r;

    if ( !r )
      return throw_( t, unexpected_end_fragment(), r );

    if ( *r == '0')
      ++r;
    else if ( *r >='1' && *r <='9' )
    {
      r = this->parse_digit(t, r);
      
      if (!try_(t)) 
        return r;
      
    }
    else
      return throw_( t, invalid_json_number( distance(r) ), r );
      

    if ( r && *r=='.' )
    {
      if ( !(++r) )
        return throw_( t, unexpected_end_fragment(), r );

      if ( *r >='0' && *r <='9')
      {
        r = this->parse_digit(t, r);
        if (!try_(t)) return r;
      }
      else
        return throw_( t, invalid_json_number( distance(r) ), r );
    }

    if (r && ( *r=='e' || *r=='E' ) )
    {
      ++r;

      if ( r && (*r=='-' || *r=='+')) 
        ++r;

      if ( !r )
        return throw_( t, unexpected_end_fragment(), r );

      if ( *r < '0' || *r > '9' )
        return throw_( t, invalid_json_number( distance(r) ), r );

      r = this->parse_digit(t, r);
      
      if (!try_(t)) 
        return r;
    }
    return r;
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> copy(T& t, R r, RD rd)
  {
    if ( rd && r && *r=='-')
      *(rd++)= *(r++);

    if ( !r )
      return throw_( t, unexpected_end_fragment(), r, rd );

    if ( *r == '0')
    {
      if ( !rd )
        return throw_( t, out_of_range(distance(r)), r, rd );
      
      *(rd++)= *(r++);
    }
    else if ( *r >='1' && *r <='9' )
    {
      r = this->copy_digit(t, r, rd);
      
      if ( !try_(t) ) 
        return std::make_pair(r, rd);
    }
    else
      return throw_( t, invalid_json_number( distance(r) ), r, rd );

    if ( r && *r=='.' )
    {
      if ( !rd )
        return throw_( t, out_of_range( distance(r) ), r, rd );
      
      *(rd++) = *(r++);
      
      if ( !r ) 
        return throw_( t, unexpected_end_fragment(), r, rd );

      if ( *r >='0' && *r <='9')
      {
        r = this->copy_digit(t, r, rd);
        if ( !try_(t) )
          return std::make_pair(r, rd);
      }
      else
        return throw_( t, invalid_json_number( distance(r) ), r, rd );
    }

    if (r && ( *r=='e' || *r=='E' ) )
    {
      if ( !rd )
        return throw_( t, out_of_range( distance(r) ), r, rd );
      
      *(rd++) = *(r++);

      if ( r && (*r=='-' || *r=='+')) 
      {
        if ( !rd )
          return throw_( t, out_of_range( distance(r) ), r, rd );

        *(rd++) = *(r++);
      }

      if ( !r )
        return throw_( t, unexpected_end_fragment(), r, rd );

      if ( *r < '0' || *r > '9' )
        return throw_( t, invalid_json_number( distance(r) ), r, rd );

      r = this->copy_digit(t, r, rd);

      if ( !try_(t) ) 
        return std::make_pair(r, rd);
    }
    return std::make_pair(r, rd);
  }


};

}}}

#endif
