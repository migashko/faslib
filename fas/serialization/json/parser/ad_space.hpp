#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_SPACE_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_SPACE_HPP

#include <fas/serialization/common/parse/ad_space_chars_t.hpp>
#include <fas/serialization/common/parse/ad_cstring_list_t.hpp>
#include <fas/serialization/common/parse/ad_space_t.hpp>
#include <fas/serialization/common/parse/ad_comment_t.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/serialization/json/except/tags.hpp>


namespace fas{ namespace json{ namespace parse{

struct ad_begin_comment:
  ::fas::serialization::parse::ad_cstring_list_t< tchars<'/', '*'>, _except_>
{};

struct ad_end_comment:
  ::fas::serialization::parse::ad_cstring_list_t< tchars<'*', '/'>, _except_>
{};

struct ad_space_chars:
  ::fas::serialization::parse::ad_space_chars_t<_except_>
{};

struct ad_comment:
  ::fas::serialization::parse::ad_comment_t<_begin_comment_, _end_comment_, _except_>
{};

struct ad_space:
  ::fas::serialization::parse::ad_space_t<_space_chars_, _comment_, _except_>
{};

struct aspect_space: aspect< type_list_n<
  advice<_begin_comment_,ad_begin_comment>,
  advice<_end_comment_,ad_end_comment>,
  advice<_space_chars_,ad_space_chars>,
  advice<_comment_,ad_comment>,
  advice<_space_,ad_space>
>::type>
{
};


}}}

#endif

/*#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_SPACE_HPP
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
*/