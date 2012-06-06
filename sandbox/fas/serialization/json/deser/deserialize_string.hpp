#ifndef FAS_SERIALIZATION_JSON_DESER_DESERIALIZE_STRING_HPP
#define FAS_SERIALIZATION_JSON_DESER_DESERIALIZE_STRING_HPP

#include <fas/serialization/json/except.hpp>

namespace fas { namespace json{

namespace detail{ namespace deser{

/// /////////////////////////////////////////////////

template<int N, typename Rin, typename Rout>
inline void utf8_copy_n(Rin& r_in, Rout& r_out)
{
  for (register int i = 0; i < N; ++i)
  {
    if (!r_in)  throw unexpected_end_fragment();
    if (!r_out) throw out_of_range( r_in.distance() );
    
    *(r_out++) = *(r_in++);
  }
}

template<typename Rin, typename Rout>
inline void utf8_copy_symbol(Rin& r_in, Rout& r_out)
{
  if (!r_in) 
    throw unexpected_end_fragment();
 
  if ( (*r_in & 128)==0 )
    *(r_out++) = *(r_in++);
  else if ( (*r_in & 224)==192 )
    utf8_copy_n<2>(r_in, r_out);
  else if ( (*r_in & 240)==224 )
    utf8_copy_n<3>(r_in, r_out);
  else if ( (*r_in & 248)==240 )
    utf8_copy_n<4>(r_in, r_out);
  else
    throw invalid_json_string( r_in.distance() );
  
}

/// /////////////////////////////////////////////////

inline unsigned short uchar2ushort(unsigned char c)
{
  
  if ( c >= '0' && c<='9' ) return c - '0';
  if ( c >= 'a' && c<='f' ) return (c - 'a') + 10;
  if ( c >= 'A' && c<='F' ) return (c - 'A') + 10;
  throw invalid_json_string();
}

template<typename Rin, typename Rout>
void deser_uhex(Rin& r_in, Rout& r_out)
{
  unsigned short hex = 0;
  if (!r_in) throw unexpected_end_fragment();
  hex |= uchar2ushort(*(r_in++)) << 12;
  if (!r_in) throw unexpected_end_fragment();
  hex |= uchar2ushort(*(r_in++)) << 8;
  if (!r_in) throw unexpected_end_fragment();
  hex |= uchar2ushort(*(r_in++)) << 4;
  if (!r_in) throw unexpected_end_fragment();
  hex |= uchar2ushort(*(r_in++));

  if ( hex <= 0x007F )
    *(r_out++) = static_cast<unsigned char>(hex);
  else if ( hex <= 0x007FF )
  {
    *(r_out++) = 192 | static_cast<unsigned char>( hex >> 6 );
    if ( !r_out ) throw out_of_range( r_in.distance() );
    *(r_out++) = 128 | ( static_cast<unsigned char>( hex ) & 63 );
  }
  else
  {
    *(r_out++) = 224 | static_cast<unsigned char>( hex >> 12 );
    if ( !r_out ) throw out_of_range( r_in.distance() );
    *(r_out++) = 128 | ( static_cast<unsigned char>( hex >> 6 ) & 63 );
    if ( !r_out ) throw out_of_range( r_in.distance() );
    *(r_out++) = 128 | ( static_cast<unsigned char>( hex ) & 63 );
  }
}



}}


template<typename Rout, typename Rin >
inline Rin deserialize_string( Rout r_out, Rin r_in  )
{
  if (!r_in) 
    throw unexpected_end_fragment();

  if ( *(r_in++) != '"' ) 
    throw expected_of("\"", r_in.distance()-1);

  for ( ;r_in && *r_in!='"'; )
  {
    if ( !r_out )
      throw out_of_range( r_in.distance() );

    if (*r_in=='\\')
    {
      if (!(++r_in)) 
        throw unexpected_end_fragment();
      
      switch (*r_in)
      {
        case '"' :
        case '\\':
        case '/' : *(r_out++) = *r_in; ++r_in; break;
        case 't':  *(r_out++) = '\t'; ++r_in; break;
        case 'b':  *(r_out++) = '\b'; ++r_in; break;
        case 'r':  *(r_out++) = '\r'; ++r_in; break;
        case 'n':  *(r_out++) = '\n'; ++r_in; break;
        case 'f':  *(r_out++) = '\f'; ++r_in; break;
        case 'u':
          detail::deser::deser_uhex( ++r_in, r_out); break;
        default:
          throw invalid_json_string( r_in.distance() );
      } // case
    }
    else
    {
      detail::deser::utf8_copy_symbol(r_in, r_out);
    }
  };

  if (!r_in) 
    throw unexpected_end_fragment();

  if ( *(r_in++) != '"' ) 
    throw expected_of("\"", r_in.distance() );

  //if ( r_out ) *r_out = '\0';
  return r_in;
};

}}

#endif
