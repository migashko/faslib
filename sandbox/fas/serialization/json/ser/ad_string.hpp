#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_AD_STRING_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_AD_STRING_HPP

#include <fas/range/range.hpp>
#include <fas/range/srange.hpp>

#include <fas/integral/bool_.hpp>
#include <fas/typemanip/is_array.hpp>

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/ser/tags.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_string_impl
{
  template<typename T, typename SR, typename R>
  R serialize_string(T& t, SR sr, R r)
  {
    r = _(t, '"', r);

    for ( ;sr && try_(t) && *sr!='\0'; ++sr )
    {
      switch ( *sr )
      {
        case '"' :
        case '\\':
        case '/' :  r = _(t, '\\', r); r = _(t, *sr, r); break;
        case '\t':  r = _(t, '\\', r); r = _(t, 't', r); break;
        case '\b':  r = _(t, '\\', r); r = _(t, 'b', r); break;
        case '\r':  r = _(t, '\\', r); r = _(t, 'r', r); break;
        case '\n':  r = _(t, '\\', r); r = _(t, 'n', r); break;
        case '\f':  r = _(t, '\\', r); r = _(t, 'f', r); break;
        default: r = _(t, *sr, r); break;
      }
    }

    r = _(t, '"', r);
    return r;
  }
  
protected:

  template<typename T, typename V, typename R>
  R _(T& t, /*typename R::value_type*/V v, R r)
  {
    if ( !try_(t) )
      return r;

    if ( !r )
      return throw_(t, out_of_range(), r);

    *r = v;
    
    return ++r;
  }
};


struct ad_string
  : ad_string_impl
{
  typedef ad_string_impl super;
 
  template<typename T, typename M, typename V>
  bool check(T&, M, const V& ) { return true; };

  // for STL containers and arrays ( char example[200] )
  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V& v, R r)
  {
    return _(t, M(), v, r, bool_<is_array<const V&>::value>() );
    // return super::serialize_string( t, ::fas::range<V>(v), r);
  }

  template<typename T, typename M, typename V, typename R>
  R _(T& t, M, const V& v, R r, true_)
  {
    return super::serialize_string( t, ::fas::srange<V>(v), r);
  }

  template<typename T, typename M, typename V, typename R>
  R _(T& t, M, const V& v, R r, false_)
  {
    return super::serialize_string( t, ::fas::range<V>(v), r);
  }
  
  template<typename T, typename M, typename R>
  R operator()(T& t, M, const char* v, R r)
  {
    if ( !v )
      return t.get_aspect().template get<_null_>()(t, M(), v, r);
    
    return super::serialize_string( t, ::fas::srange(v), r);
  }

  template<typename T, typename M, typename R>
  R operator()(T& t, M, const wchar_t* v, R r)
  {
    if ( !v )
      return t.get_aspect().template get<_null_>(t, M(), v, r);
    
    return super::serialize_string( t, ::fas::srange(v), r);
  }
  
};

struct ad_cstring
  : ad_string_impl
{
  typedef ad_string_impl super;
  
  template<typename T, typename M, typename V>
  bool check(T&, M, const V& v)
  {
    return true;
  };

  // for STL containers and arrays ( char example[200] )
  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V&, R r)
  {
    return super::serialize_string( t, M().get_range(), r);
  }
};

}}}

#endif
