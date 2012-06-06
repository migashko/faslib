#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_SIMPLE_STRING_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_SIMPLE_STRING_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/expected_of.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/parser/tags.hpp>

namespace fas{ namespace json{ namespace parse{

struct ad_simple_string
{

  template<typename T, typename R>
  bool check( T&, R r) {  return r && *r=='"' ; }
  
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


  template<typename T, typename R>
  R parse(T& t, R r)
  {
    if (!r)
      return throw_( t, unexpected_end_fragment(), r);

    if (*r!='"') 
      return throw_( t, expected_of("\"",  r.distance() ), r);

    for ( ++r; r && *r!='"'; ++r);

    if (!r)
      return throw_( t, unexpected_end_fragment(), r);

    if (*r!='"')
      return throw_( t, expected_of("\"", r.distance() ), r);

    return ++r;
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> copy(T& t, R r, RD rd)
  {
    if (!r)
      return throw_( t, unexpected_end_fragment(), r, rd);

    if (*r!='"') 
      return throw_( t, expected_of("\"",  r.distance() ), r, rd);

    if (!rd) 
      return throw_( t, out_of_range(), r, rd);
    
    *(rd++)=*(r++);
    
    for ( ; r && *r!='"'; ++r, ++rd) 
    {
      if (!rd) 
        return throw_( t, out_of_range(), r, rd);
      *rd=*r;
    }

    if (!r)
      return throw_( t, unexpected_end_fragment(), r, rd);

    if (*r!='"')
      return throw_( t, expected_of("\"", r.distance() ), r, rd);

    if (!rd) 
      return throw_( t, out_of_range(), r, rd);
    
    *(rd++)=*(r++);

    return std::make_pair(r, rd);
  }

};

}}}

#endif
