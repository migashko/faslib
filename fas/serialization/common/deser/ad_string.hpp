#ifndef FAS_SERIALIZATION_COMMON_DESER_AD_STRING_T_HPP
#define FAS_SERIALIZATION_COMMON_DESER_AD_STRING_T_HPP

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


/// 
#include <fas/range/range.hpp>
#include <iostream>
#include <string>

namespace fas{ namespace serialization{ namespace deser{

template<typename TgExcept>
struct ad_utf8
{
	typedef TgExcept _except_;

  template<typename T, typename Rin, typename Rout>
  Rin operator()(T& t, Rin r_in, Rout& r_out)
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
     return throw_t<_except_>(t, invalid_string( distance(r_in) ), r_in );
   return r_in;
  }

private:
	
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
};
	
template<typename TgExcept>
struct ad_json_uhex
{
	typedef TgExcept _except_;

	template<typename R>
	bool check(R r)
	{
		return *r=='u';
	}
	

	template<typename T, typename Rin, typename Rout>
	Rin operator()( T& t, Rin r_in, Rout& r_out)
	{
		if ( !r_in )
			return throw_t<_except_>(t, unexpected_end_fragment(), r_in );
		
    unsigned short hex = 0;

		const unsigned short fail_value = static_cast<unsigned short>(-1);
		unsigned short value = uchar2ushort(r_in++);
		
		// //////////////
		if ( value != fail_value )
			hex |= value << 12;
		else
			return throw_t<_except_>(t, invalid_string( distance(r_in) ), r_in );

    if (!r_in)
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );

		// //////////////
		value = uchar2ushort(r_in++);
		if ( value != fail_value )
			hex |= value << 8;
		else
			return throw_t<_except_>(t, invalid_string( distance(r_in) ), r_in );

    if (!r_in)
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );

		// //////////////
		value = uchar2ushort(r_in++);
		if ( value != fail_value )
			hex |= value << 4;
		else
			return throw_t<_except_>(t, invalid_string( distance(r_in) ), r_in );

    if (!r_in)
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );

		// //////////////

		value = uchar2ushort(r_in++);
		if ( value != fail_value )
			hex |= value;
		else
			return throw_t<_except_>(t, invalid_string( distance(r_in) ), r_in );

		// //////////////
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

  template<typename R>
  unsigned short uchar2ushort(R c)
  {
    register unsigned short ch = *c;
    if ( ch >= '0' && ch<='9' ) return ch - '0';
    if ( ch >= 'a' && ch<='f' ) return (ch - 'a') + 10;
    if ( ch >= 'A' && ch<='F' ) return (ch - 'A') + 10;
    return static_cast<unsigned short>(-1);
  }
};
	
template<typename TgUhex, typename TgExcept>
struct ad_json_escape
{
	typedef TgUhex 	 _json_uhex_;
	typedef TgExcept _except_;
	template<typename R>
	bool check(R r)
	{
		return *r=='\\';
	}

	template<typename T, typename Rin, typename Rout>
	Rin operator()( T& t, Rin r_in, Rout& r_out)
	{
		if ( !r_in )
			return r_in;
		
	  if (*r_in!='\\')
			return r_in;

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
			case 'u':  r_in = t.get_aspect().template get<_json_uhex_>()(t,  ++r_in, r_out); break;
			default:
				return throw_t<_except_>(t, invalid_string( distance(r_in) ), r_in );
		} // case

		return r_in;
	}
};

template<typename TgSep, typename TgUtf8, typename TgEscape, typename TgExcept>
struct ad_jsonbase_string_t
{
	typedef TgUtf8 _utf8_;
  typedef TgSep _separator_;
	typedef TgEscape _escape_;
  typedef TgExcept _except_;
  
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    return _1(t, M(), v, r, bool_<is_array<V>::value> () );
  }

    
  template<typename T, typename M, typename V, typename R, typename ISA>
  R _1(T& t, M, V& v, R r, ISA)
  {
    return _(t, M(), orange(v, true), r, false_() );
  }

  template<typename T, typename M, typename V, typename R>
  R _1(T& t, M, V* v, R r, false_)
  {
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
    for ( ;r_in && try_t<_except_>(t) ; )
    {
      if (!r_out)
        return throw_t<_except_>(t, out_of_range( distance(r_in) ), r_in );

			if ( t.get_aspect().template get<_separator_>().check(t, M(), r_in) )
        return r_in;
			
			if ( t.get_aspect().template get<_escape_>().check(r_in) )
        r_in = t.get_aspect().template get<_escape_>()(t, r_in, r_out);
      else
				r_in = t.get_aspect().template get<_utf8_>()(t, r_in, r_out);
    };
    return r_in;
  };
};

template<typename TgContentString, typename TgQuotes,  typename TgParseString, typename TgParseNull, typename TgExcept>
struct ad_json_string_t
{
	typedef TgContentString _content_string_;
  typedef TgQuotes _quotes_;
  typedef TgParseString _parse_string_;
  typedef TgParseNull _parse_null_;
	typedef TgExcept _except_;
  
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
    r = t.get_aspect().template get<_content_string_>()(t, M(), v, r);
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

}}}

#endif
