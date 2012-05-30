#ifndef FAS_SERIALIZATION_COMMON_DESER_AD_JSON_UHEX_T_HPP
#define FAS_SERIALIZATION_COMMON_DESER_AD_JSON_UHEX_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>
#include <fas/serialization/common/except/out_of_range.hpp>
#include <fas/serialization/common/except/unexpected_end_fragment.hpp>
#include <fas/serialization/common/except/invalid_string.hpp>
#include <fas/range/distance.hpp>

namespace fas{ namespace serialization{ namespace deser{
  
template<typename TgExcept>
struct ad_json_uhex_t
{
  typedef TgExcept _except_;

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

}}}

#endif
