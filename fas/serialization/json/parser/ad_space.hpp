#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_SPACE_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_SPACE_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/parser/tags.hpp>

namespace fas{ namespace json{ namespace parse{

struct ad_space
{
  template<typename R>
  bool check(R r) const { return *r==' ' || *r=='\t' || *r=='\r' || *r=='\n'; }

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
  
  template<typename R>
  bool is_begin_comment(R r) const
  {
    if ( *r != '/' )
      return false;
    
    R r2 = r;
    ++r2;
    return r2 && (*r2 == '*' );
  }

  template<typename R>
  bool is_end_comment(R r) const
  {
    if ( *r != '*' )
      return false;
    
    R r2 = r;
    ++r2;
    return r2 && (*r2 == '/' );
  }

  template<typename T, typename R>
  R parse(T& t, R r)
  {
    bool start_comment = false;

    while ( r )
    {
      if ( start_comment )
      {
        if ( is_end_comment(r) )
        {
          start_comment = false;
          ++r;++r;
          continue;
        }
      }
      else
      {
        if ( !check(r) )
        {
          if ( is_begin_comment(r) )
          {
            start_comment = true;
            ++r;++r;
            continue;
          }
          return r;
        }
      }
      ++r;
    }

    if ( start_comment )
      return throw_( t, unexpected_end_fragment("unterminated comment"), r);
      
    return r;
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> copy(T& t, R r, RD rd)
  {
    return std::make_pair(parse(t, r), rd);
  }
  

};

}}}

#endif
