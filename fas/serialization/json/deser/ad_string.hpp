#ifndef FAS_SERIALIZATION_JSON_DESER_AD_STRING_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_STRING_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/invalid_json_string.hpp>
#include <fas/serialization/json/except/expected_of.hpp>

#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>

// #include <fas/range/range.hpp>

//#include <fas/typemanip/type2type.hpp>
#include <fas/typemanip/is_array.hpp>
#include <fas/range/range.hpp>
#include <fas/range/orange.hpp>
#include <fas/range/distance.hpp>

#include <iostream>
namespace fas{ namespace json{ namespace deser{

using ::fas::serialization::throw_t;
using ::fas::serialization::try_t;

template<typename TgSep, typename TgExcept>
struct ad_jsonbase_string_t
{
  typedef TgSep _separator_;
  typedef TgExcept _except_;
  
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return true;
    /*
    return t.get_aspect().template get<parse::_string_>().check(r)
           || t.get_aspect().template get<parse::_null_>().check(r);
           */
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    /*if ( t.get_aspect().template get<parse::_null_>().check(r) )
    {
      orange(v, true);
      return t.get_aspect().template get<parse::_null_>()(t, r);
    }*/

    return _1(t, M(), v, r, bool_<is_array<V>::value> () );
  }

    
  template<typename T, typename M, typename V, typename R, typename ISA>
  R _1(T& t, M, V& v, R r, ISA)
  {
    /*if ( t.get_aspect().template get<parse::_null_>().check(r) )
      r = t.get_aspect().template get<parse::_null_>()(t, r);
    else*/ // if ( t.get_aspect().template get<parse::_string_>().check(r) )
    r = _(t, M(), orange(v, !ISA::value), r, ISA() );
    return r;
  }

  template<typename T, typename M, typename V, typename R>
  R _1(T& t, M, V* v, R r, false_)
  {
    using namespace ::fas::json;

    /*if ( t.get_aspect().template get<parse::_null_>().check(r) )
      r = t.get_aspect().template get<parse::_null_>()(t, r);
    else*/ /*if ( !v )
      r = t.get_aspect().template get<parse::_string_>()(t, r);
    else if ( t.get_aspect().template get<parse::_string_>().check(r) )
      */
    if ( !v )
      return r;
    r = _(t, M(), range(v, v + M::limit ), r, true_() );

    return r;
  }

protected:

  template<typename T, typename M, typename Rout, typename Rin >
  Rin _( T& t, M, Rout r_out, Rin r_in, false_ )
  {
    return deserialize_string(t, M(), r_out, r_in);
  }

  template<typename T, typename M, typename Rout, typename Rin >
  Rin _( T& t, M, Rout r_out, Rin r_in, true_   )
  {
    r_in = deserialize_string(t, M(), r_out, r_in);
    
    if ( !try_t<_except_>(t) ) 
      return r_in;
    
    if ( !r_out )
      return throw_t<_except_>(t, out_of_range( distance(r_in) ), r_in );
    
    *(r_out++) = '\0';
    
    return r_in;
  }

  template<typename T, typename M, typename Rout, typename Rin >
  Rin deserialize_string( T& t, M, Rout& r_out, Rin r_in  )
  {
    /*
    if (!r_in)
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );
  
    if ( *r_in != '"' )
      return throw_t<_except_>(t, expected_of("\"", distance(r_in) ), r_in );
    */
      
    for ( /*++r_in*/ ;r_in && try_(t) /*&& *r_in!='"'*/; )
    {
      if (!r_out)
        return throw_t<_except_>(t, out_of_range( distance(r_in) ), r_in );
      if ( t.get_aspect().template get<_separator_>().check(t, M(), r_in) )
        return r_in;

      if (*r_in=='\\')
      {
        if (!(++r_in)) 
          return throw_t<_except_>(t, unexpected_end_fragment(), r_in );
      
        switch (*r_in)
        {
          case '"' :
          case '\\':
          case '/' : *(r_out++) = *r_in; ++r_in; break;
          case 't':  *(r_out++) = '\t';  ++r_in; break;
          case 'b':  *(r_out++) = '\b';  ++r_in; break;
          case 'r':  *(r_out++) = '\r';  ++r_in; break;
          case 'n':  *(r_out++) = '\n';  ++r_in; break;
          case 'f':  *(r_out++) = '\f';  ++r_in; break;
          case 'u':
            r_in = deser_uhex(t,  ++r_in, r_out); break;
          default:
            return throw_t<_except_>(t, invalid_json_string( distance(r_in) ), r_in );
            
        } // case
      }
      else
      {
        r_in = utf8_copy_symbol(t, r_in, r_out);
      }
    };

    /*
    if (!r_in) 
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );

    if ( *(r_in++) != '"' )
      return throw_t<_except_>(t, expected_of("\"", distance(r_in) ), r_in );
    */
    
    return r_in;
  };

  template<int N, typename T, typename Rin, typename Rout>
  Rin utf8_copy_n(T& t, Rin r_in, Rout& r_out)
  {
    for (register int i = 0; i < N; ++i)
    {
      if (!r_in)
        return throw_t<_except_>(t, unexpected_end_fragment(), r_in );
      
      if (!r_out)
        return throw_t<_except_>(t, out_of_range( distance(r_in) ), r_in );
      
      *(r_out++) = *(r_in++);
    }
    
    return r_in;
  }

  template<typename T, typename Rin, typename Rout>
  Rin utf8_copy_symbol(T& t, Rin r_in, Rout& r_out)
  {
    if (!r_in) 
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );
 
   if ( (*r_in & 128)==0 )
     *(r_out++) = *(r_in++);
   else if ( (*r_in & 224)==192 )
     return utf8_copy_n<2>(t, r_in, r_out);
   else if ( (*r_in & 240)==224 )
     return utf8_copy_n<3>(t, r_in, r_out);
   else if ( (*r_in & 248)==240 )
     return utf8_copy_n<4>(t, r_in, r_out);
   else
     return throw_t<_except_>(t, invalid_json_string( distance(r_in) ), r_in );
   return r_in;
 }

/// /////////////////////////////////////////////////

  template<typename T, typename R>
  unsigned short uchar2ushort(T& t, R c)
  {
    register unsigned short ch = *c;
    if ( ch >= '0' && ch<='9' ) return ch - '0';
    if ( ch >= 'a' && ch<='f' ) return (ch - 'a') + 10;
    if ( ch >= 'A' && ch<='F' ) return (ch - 'A') + 10;
    throw_t<_except_>(t, invalid_json_string( distance(c) ), c );
    return 0;
  }

  template<typename T, typename Rin, typename Rout>
  Rin deser_uhex(T& t, Rin r_in, Rout& r_out)
  {
    unsigned short hex = 0;
  
    if (!r_in)
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );

    hex |= uchar2ushort(t, r_in++ ) << 12;
    
    if ( !try_t<_except_>(t) )
      return r_in;
  
    if (!r_in)
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );
  
    hex |= uchar2ushort(t, r_in++) << 8;

    if ( !try_t<_except_>(t) )
      return r_in;
    
    if (!r_in)
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );
  
    hex |= uchar2ushort(t, r_in++) << 4;

    if ( !try_t<_except_>(t) )
      return r_in;

    if (!r_in)
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );

    hex |= uchar2ushort(t, r_in++);

    if ( !try_t<_except_>(t) )
      return r_in;

    if ( hex <= 0x007F )
      *(r_out++) = static_cast<unsigned char>(hex);
    else if ( hex <= 0x007FF )
    {
      *(r_out++) = 192 | static_cast<unsigned char>( hex >> 6 );

      if ( !r_out )
        return throw_t<_except_>(t, out_of_range( distance(r_in) ), r_in );
    
      *(r_out++) = 128 | ( static_cast<unsigned char>( hex ) & 63 );
    }
    else
    {
      *(r_out++) = 224 | static_cast<unsigned char>( hex >> 12 );

      if ( !r_out )
        return throw_t<_except_>(t, out_of_range( distance(r_in) ), r_in );
    
      *(r_out++) = 128 | ( static_cast<unsigned char>( hex >> 6 ) & 63 );
    
      if ( !r_out )
        return throw_t<_except_>(t, out_of_range( distance(r_in) ), r_in );
    
      *(r_out++) = 128 | ( static_cast<unsigned char>( hex ) & 63 );
    }
    return r_in;
  }
};

template<typename TgQuotes,  typename TgParseString, typename TgParseNull, typename TgExcept>
struct ad_json_string_t: ad_jsonbase_string_t<TgQuotes, TgExcept>
{
  typedef ad_jsonbase_string_t<TgQuotes, TgExcept> super;
  typedef TgQuotes _quotes_;
  typedef TgParseString _parse_string_;
  typedef TgParseNull _parse_null_;
  
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return t.get_aspect().template get<_parse_string_>().check(r)
           || t.get_aspect().template get<_parse_null_>().check(r);

  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    if ( t.get_aspect().template get<_parse_null_>().check(r) )
    {
      _clear(v);
      return t.get_aspect().template get<_parse_null_>()(t, r);
    }
    
    if ( !t.get_aspect().template get<_parse_string_>().check(r) )
      return r;
    
    typedef typename T::aspect::template advice_cast<_quotes_>::type::separator separator;

    if (!r)
      return throw_t<_except_>(t, unexpected_end_fragment(), r );

    if ( !t.get_aspect().template get<_quotes_>().check(t, M(), r) )
      return throw_t< _except_ >( t, expected_of( separator()(), distance(r) ), r );
    R beg_string = r;
    r = t.get_aspect().template get<_quotes_>()(t, M(), v, r);
    R income = r;
    r = super::operator()(t, M(), v, r);
    if ( r == income )
      return t.get_aspect().template get<_parse_string_>()(t, beg_string);
      
    if ( !t.get_aspect().template get<_quotes_>().check(t, M(), r) )
      return throw_t< _except_ >( t, expected_of( separator()(), distance(r) ), r );
    r = t.get_aspect().template get<_quotes_>()(t, M(), v, r);
    
    return r;
  }
private:
  template<typename V>
  void _clear(V* v)  { if (v) v[0]='\0'; }

  template<typename V>
  void _clear(V& v)  { orange(v, true); }

  
};


struct ad_string: ad_json_string_t<_quotes_, parse::_string_, parse::_null_, _except_>
{
};

struct ad_cstring
{
private:
  template<typename R, typename RS>
  bool _check(R& r, RS rs)
  {
    for ( ;r && rs && *r==*rs; ++r, ++rs );
    return !rs && r && *r=='"';
  }
public:

  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return t.get_aspect().template get<parse::_string_>().check(r);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V&, R r)
  {
    if ( !t.get_aspect().template get<parse::_string_>().check(r) )
      return r;

    R income =  r;
    if (!_check(++r, M().get_range() ) )
    {
      if (!r)
        throw unexpected_end_fragment();
      return income;
    }
    if (!r)
      throw unexpected_end_fragment();

    if ( *r++ != '"')
      return income;
    
    return r;
  }
};

}}}

#endif
