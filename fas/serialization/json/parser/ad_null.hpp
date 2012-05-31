#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_NULL_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_NULL_HPP

#include <fas/serialization/common/parse/ad_json_null_t.hpp>
#include <fas/serialization/json/except/tags.hpp>

namespace fas{ namespace json{ namespace parse{

struct ad_null:
	::fas::serialization::parse::ad_json_null_t<_except_>
{};

}}}

#endif

/*
 #ifndef FAS_SERIALIZATION_JSON_PARSER_AD_NULL_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_NULL_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/expected_of.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/distance.hpp>


namespace fas{ namespace json{ namespace parse{

struct ad_null
{
  template<typename R>
  bool check( R r) 
  {
    return r && *r=='n'; 
  }

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
    if (!r)
      return throw_( t, unexpected_end_fragment("expected of null"), r);

    if ( *r!='n' )
      return throw_( t, expected_of("null", distance(r) ), r);
      

    if ( ++r && *r=='u'&& ++r && *r=='l'&& ++r && *r=='l' )
      return ++r;

    if (!r)
      return throw_( t, unexpected_end_fragment("expected of null"), r);

    return throw_( t, expected_of("null", distance(r) ), r);
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> copy( T& t, R r, RD rd)
  {
    r = parse(t, r);
    
    if ( !try_(t) )
      return std::make_pair( r, rd );
    
    if ( rd ) *(rd++)='n';
    if ( rd ) *(rd++)='u';
    if ( rd ) *(rd++)='l';
    if ( rd ) *(rd++)='l';
    else 
      return throw_( t, out_of_range("null"), r, rd );
    
    return std::make_pair(r, rd);
  }
};

}}}

#endif
*/