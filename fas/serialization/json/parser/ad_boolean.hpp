#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_BOOLEAN_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_BOOLEAN_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/expected_of.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/distance.hpp>

namespace fas{ namespace json{ namespace parser{

struct ad_boolean
{
  template<typename R>
  bool check( R r) {  return r && (*r=='t' || *r=='f'); }

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
  R parse(T& t, R r)
  {
    if ( !r )
      return throw_( t, unexpected_end_fragment("expected of bool"), r );

    if ( *r!='t' && *r!='f' )
      return throw_( t, expected_of("true or false", distance(r) ), r );

    if (*r=='t')
    {
      if ( ++r && *r=='r'&& ++r && *r=='u'&& ++r && *r=='e' )
        return ++r;
    }
    else
    {
      if ( ++r && *r=='a'&& ++r && *r=='l'&& ++r && *r=='s' && ++r && *r=='e' )
        return ++r;
    }

    if (!r)
      return throw_( t, unexpected_end_fragment("expected of true or false"), r );
      
    return throw_( t, expected_of("true or false", distance(r) ), r );
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> copy(T& t, R r, RD rd)
  {
    if ( !r )
      return throw_( t, unexpected_end_fragment("expected of bool"), r, rd);
    
    if ( *r!='t' && *r!='f' )
      return throw_( t, expected_of("true or false", distance(r) ), r, rd);
    
    if ( !rd )
      return throw_( t, out_of_range( distance(r) ), r, rd ) ;

      
    if (*r=='t')
    {
      if ( ++r && *r=='r' && ++r && *r=='u'&& ++r && *r=='e' )
      {
        if (rd) *(rd++) = 't'; 
        if (rd) *(rd++) = 'r'; 
        if (rd) *(rd++) = 'u'; 
        if (rd) *(rd++) = 'e';
        else 
          return throw_( t, out_of_range( distance(r) ), r, rd ) ;
          
        return std::make_pair(++r, rd);
      }
    }
    else
    {
      if ( ++r && *r=='a'&& ++r && *r=='l'&& ++r && *r=='s' && ++r && *r=='e' )
      {
        if (rd) *(rd++) = 'f'; 
        if (rd) *(rd++) = 'a'; 
        if (rd) *(rd++) = 'l'; 
        if (rd) *(rd++) = 's'; 
        if (rd) *(rd++) = 'e';
        else 
          return throw_( t, out_of_range( distance(r) ), r, rd ) ;
        return std::make_pair(++r, rd);
      }
    }

    if (!r) 
      return throw_( t, unexpected_end_fragment("expected of true or false"), r, rd );
    
    return throw_( t, expected_of("true or false", distance(r) ), r, rd);
  }
};

}}}

#endif
