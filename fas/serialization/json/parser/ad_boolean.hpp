#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_BOOLEAN_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_BOOLEAN_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/expected_of.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/distance.hpp>

#include <fas/typemanip/tchars.hpp>
#include <fas/range/srange.hpp>

namespace fas{ namespace json{ namespace parse{

template<typename SEP>
struct ad_chars
{
  typedef typename normalize<SEP>::type chars_list;
  
  template<typename R>
  bool check( R r) 
  {
    return _check_list(r, chars_list() );
  }
  
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    return _parse_list(t, r, chars_list() );
  }
  
  template<typename T, typename R, typename RO>
  std::pair<R, RO> operator()(T& t, R r, RO ro)
  {
    //return _copy(t, r, srange(chars_type()()), ro );
     return _copy_list(t, r, chars_list(), ro );
  }


  
private:
  
  template<typename R, typename LL, typename LR>
  bool _check_list(R r, type_list<LL, LR>)
  {
    if ( _check(r, srange(LL()()) ) )
      return true;
    return _check_list( r, LR() );
  }

  template<typename R>
  bool _check_list(R r, empty_list)
  {
    return false;
  }

  template<typename R, typename RR>
  bool _check(R r, RR rr)
  {
    for ( ;r && rr && *r==*rr; ++r, ++rr);
    return !rr;
  }

  template<typename T, typename R, typename LL, typename LR>
  R _parse_list(T& t, R r, type_list<LL, LR>)
  {
    if ( _check(r, srange(LL()()) ) )
      return _parse(t, r, srange(LL()()) );
    return _parse_list( t, r, LR() );
  }

  template<typename T, typename R>
  R _parse_list(T& t, R r, empty_list)
  {
    return throw_( t, expected_of( typename chars_list::left_type()(), distance(r) ), r );;
  }

  template<typename T, typename R, typename RR>
  R _parse(T& t, R r, RR rr)
  {
    for ( ;r && rr /*&& *r==*rr*/; ++r, ++rr);
    
    /*if (rr && !r)
      return throw_( t, unexpected_end_fragment(), r );
    
    if (rr)
      return throw_( t, expected_of( typename chars_list::left_type()(), distance(r) ), r );
    */
    
    return r;
  }
  
  template<typename T, typename R, typename LL, typename LR, typename RO>
  std::pair<R, RO> _copy_list(T& t, R r, type_list<LL, LR>, RO ro)
  {
    if ( _check(r, srange(LL()()) ) )
      return _copy(t, r, srange(LL()()), ro);
    return _copy_list( t, r, LR(), ro );
  }

  template<typename T, typename R, typename RO>
  std::pair<R, RO> _copy_list(T& t, R r, empty_list, RO ro)
  {
    return throw_( t, expected_of( typename chars_list::left_type()(), distance(r) ), r, ro );
  }

  template<typename T, typename R, typename RR, typename RO>
  std::pair<R, RO> _copy(T& t, R r, RR rr, RO ro)
  {
    for ( ;r && rr && ro && *r==*rr; ++r, ++rr)
      *(ro++) = *r;
    
    if (rr && !r)
      return throw_( t, unexpected_end_fragment(), r, ro );

    if (rr && !ro)
      return throw_( t, out_of_range( distance(r) ), r, ro );

    if (rr)
      return throw_( t, expected_of( typename chars_list::left_type()(), distance(r) ), r, ro);
    
    return std::make_pair(r, ro);
  }

};

struct ad_true: ad_chars< tchars<'t', 'r', 'u', 'e'> >  {};
struct ad_false: ad_chars< tchars<'f', 'a', 'l', 's', 'e'> >  {};

struct ad_boolean: ad_chars< 
  type_list_n<
    tchars<'t', 'r', 'u', 'e'>,
    tchars<'f', 'a', 'l', 's', 'e'> 
  >::type
>
{};
struct ad_boolean1
{
  template<typename R>
  bool check( R r) 
  {
    return ad_true().check(r) || ad_false().check(r);
    // return r && (*r=='t' || *r=='f'); 
  }

  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    if ( ad_true().check(r) )
      return ad_true()(t, r);
    else if ( ad_false().check(r) )
      return ad_false()(t, r);
    return throw_( t, expected_of("true or false", distance(r) ), r );
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> operator()(T& t, R r, RD rd)
  {
    if ( ad_true().check(r) )
      return ad_true()(t, r, rd);
    else if ( ad_false().check(r) )
      return ad_false()(t, r, rd);
    return throw_( t, expected_of("true or false", distance(r) ), r, rd );

    // return this->copy(t, r, rd);
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
