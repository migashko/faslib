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
#include <fas/range/distance.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_string
{
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return t.get_aspect().template get<parser::_string_>().check(r)
           || t.get_aspect().template get<parser::_null_>().check(r);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    return _1(t, M(), v, r, typename is_array<V>::type() );
  }

    
  template<typename T, typename M, typename V, typename R, typename ISA>
  R _1(T& t, M, V& v, R r, ISA)
  {
    //using namespace ::fas::json;
    
    if ( t.get_aspect().template get<parser::_null_>().check(r) )
      r = t.get_aspect().template get<parser::_null_>()(t, r);
    else if ( t.get_aspect().template get<parser::_string_>().check(r) )
      r = _(t, init_range(v, !ISA::value), r, /*typename is_array<V>::type*/ISA() );
    
    return r;
  }

  template<typename T, typename M, typename V, typename R>
  R _1(T& t, M, V* v, R r, false_)
  {
    using namespace ::fas::json;

    if ( t.get_aspect().template get<parser::_null_>().check(r) )
      r = t.get_aspect().template get<parser::_null_>()(t, r);
    else if ( !v )
      r = t.get_aspect().template get<parser::_string_>()(t, r);
    else if ( t.get_aspect().template get<parser::_string_>().check(r) )
      r = _(t, range(v, v + M::limit ), r, true_() );

    return r;
  }

protected:

  template<typename T, typename Rout, typename Rin/*, typename S*/ >
  Rin _( T& t, Rout r_out, Rin r_in, /*type2type<S> */ false_ )
  {
    return deserialize_string(t, r_out, r_in);
  }

  template<typename T, typename Rout, typename Rin/*, typename S, int N*/ >
  Rin _( T& t, Rout r_out, Rin r_in, /*type2type<S[N]>*/ true_   )
  {
    r_in = deserialize_string(t, r_out, r_in);
    
    if ( !try_(t) ) 
      return r_in;
    
    if ( !r_out )
      return throw_(t, out_of_range( distance(r_in) ), r_in );
    
    *(r_out++) = '\0';
    
    return r_in;
  }

  template<typename T, typename Rout, typename Rin >
  Rin deserialize_string( T& t, Rout& r_out, Rin r_in  )
  {
    if (!r_in)
      return throw_(t, unexpected_end_fragment(), r_in );
  
    if ( *r_in != '"' )
      return throw_(t, expected_of("\"", distance(r_in) ), r_in );
      
    for ( ++r_in ;r_in && try_(t) && *r_in!='"'; )
    {
      if (!r_out)
        return throw_(t, out_of_range( distance(r_in) ), r_in );

      if (*r_in=='\\')
      {
        if (!(++r_in)) 
          return throw_(t, unexpected_end_fragment(), r_in );
      
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
            return throw_(t, invalid_json_string( distance(r_in) ), r_in );
            
        } // case
      }
      else
      {
        r_in = utf8_copy_symbol(t, r_in, r_out);
      }
    };

    if (!r_in) 
      return throw_(t, unexpected_end_fragment(), r_in );

    if ( *(r_in++) != '"' )
      return throw_(t, expected_of("\"", distance(r_in) ), r_in );
    
    return r_in;
  };

  template<int N, typename T, typename Rin, typename Rout>
  Rin utf8_copy_n(T& t, Rin r_in, Rout& r_out)
  {
    for (register int i = 0; i < N; ++i)
    {
      if (!r_in)
        return throw_(t, unexpected_end_fragment(), r_in );
      
      if (!r_out)
        return throw_(t, out_of_range( distance(r_in) ), r_in );
      
      *(r_out++) = *(r_in++);
    }
    
    return r_in;
  }

  template<typename T, typename Rin, typename Rout>
  Rin utf8_copy_symbol(T& t, Rin r_in, Rout& r_out)
  {
    if (!r_in) 
      return throw_(t, unexpected_end_fragment(), r_in );
 
   if ( (*r_in & 128)==0 )
     *(r_out++) = *(r_in++);
   else if ( (*r_in & 224)==192 )
     return utf8_copy_n<2>(t, r_in, r_out);
   else if ( (*r_in & 240)==224 )
     return utf8_copy_n<3>(t, r_in, r_out);
   else if ( (*r_in & 248)==240 )
     return utf8_copy_n<4>(t, r_in, r_out);
   else
     return throw_(t, invalid_json_string( distance(r_in) ), r_in );
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
    throw_(t, invalid_json_string( distance(c) ) );
    return 0;
  }

  template<typename T, typename Rin, typename Rout>
  Rin deser_uhex(T& t, Rin r_in, Rout& r_out)
  {
    unsigned short hex = 0;
  
    if (!r_in)
      return throw_(t, unexpected_end_fragment(), r_in );

    hex |= uchar2ushort(t, r_in++ ) << 12;
    
    if ( !try_(t) )
      return r_in;
  
    if (!r_in)
      return throw_(t, unexpected_end_fragment(), r_in );
  
    hex |= uchar2ushort(t, r_in++) << 8;

    if ( !try_(t) )
      return r_in;
    
    if (!r_in)
      return throw_(t, unexpected_end_fragment(), r_in );
  
    hex |= uchar2ushort(t, r_in++) << 4;

    if ( !try_(t) )
      return r_in;

    if (!r_in)
      return throw_(t, unexpected_end_fragment(), r_in );

    hex |= uchar2ushort(t, r_in++);

    if ( !try_(t) )
      return r_in;

    if ( hex <= 0x007F )
      *(r_out++) = static_cast<unsigned char>(hex);
    else if ( hex <= 0x007FF )
    {
      *(r_out++) = 192 | static_cast<unsigned char>( hex >> 6 );

      if ( !r_out )
        return throw_(t, out_of_range( distance(r_in) ), r_in );
    
      *(r_out++) = 128 | ( static_cast<unsigned char>( hex ) & 63 );
    }
    else
    {
      *(r_out++) = 224 | static_cast<unsigned char>( hex >> 12 );

      if ( !r_out )
        return throw_(t, out_of_range( distance(r_in) ), r_in );
    
      *(r_out++) = 128 | ( static_cast<unsigned char>( hex >> 6 ) & 63 );
    
      if ( !r_out )
        return throw_(t, out_of_range( distance(r_in) ), r_in );
    
      *(r_out++) = 128 | ( static_cast<unsigned char>( hex ) & 63 );
    }
    return r_in;
  }

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
    return t.get_aspect().template get<parser::_string_>().check(r);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V&, R r)
  {
    if ( !t.get_aspect().template get<parser::_string_>().check(r) )
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
