//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_XTIME_XSPAN_HPP
#define FAS_XTIME_XSPAN_HPP

#include <fas/xtime/types.hpp>

namespace fas {

template<long F, long T>
inline long xsec_convert(long xsec)
{
  return static_cast<long> ( static_cast<xsec_t>( xsec ) * T / F );
}

template<long I>
struct xspan
{
  static const xsec_t xmax = I;

  template<long F>
  static long convert(long xsec)
  {
    return static_cast<long> ( static_cast<xsec_t>( xsec ) * xmax / F );
  }

  long sec;

  long xsec;

  xspan()
    : sec(0)
    , xsec(0)
  {}

  template<long X>
  xspan(const xspan<X>& span )
    : sec(span.sec)
    , xsec( convert<xspan<X>::xmax>(span.xsec))
  {}

  xspan(long sec, long xsec)
    : sec(sec)
    , xsec(xsec)
  {}

  xspan(int sec)
    : sec(sec)
    , xsec(0)
  {}

  xspan(long sec)
    : sec(sec)
    , xsec(0)
  {}

  xspan(float s)
    : sec( static_cast<long>(s) )
    , xsec( static_cast<long>( (s - sec)*xmax ) )
  {}

  xspan(double s)
    : sec( static_cast<long>(s) )
    , xsec( static_cast<long>( (s - sec)*xmax  ) )
  {}

  xsec_t to_nanosec() const
  {
    return ( static_cast<xsec_t>(sec) * xmax + xsec) * (FAS_NANOSEC/xmax );
  }

  xsec_t to_microsec() const
  {
    return to_nanosec()/1000;
  }

  xsec_t to_millisec() const
  {
    return to_nanosec()/1000000;
  }

  xsec_t to_centisec() const
  {
    return to_nanosec()/10000000;
  }

  xsec_t to_decisec() const
  {
    return to_nanosec()/100000000;
  }

  float to_float() const
  {
    return static_cast<float>( to_nanosec() ) / xmax;
  }

  double to_double() const
  {
    return static_cast<double>( to_nanosec() ) / xmax;
  }

  template<long X>
  xspan& operator += (const xspan<X>& s)
  {
    *this = *this + s;
    return *this;
  }

  template<typename T>
  xspan& operator += (const T& s)
  {
    *this = *this + xspan<I>(s);
    return *this;
  }

  template<long X>
  xspan& operator -= (const xspan<X>& s)
  {
    *this = *this - s;
    return *this;
  }

  template<typename T>
  xspan& operator -= (const T& s)
  {
    *this = *this - xspan<I>(s);
    return *this;
  }

  template<long X>
  xspan& operator /= (const xspan<X>& s)
  {
    *this = *this / s;
    return *this;
  }

  template<typename T>
  xspan& operator /= (const T& s)
  {
    *this = *this / xspan<I>(s);
    return *this;
  }

  template<long X>
  xspan& operator *= (const xspan<X>& s)
  {
    *this = *this * s;
    return *this;
  }

  template<typename T>
  xspan& operator *= (const T& s)
  {
    *this = *this * xspan<I>(s);
    return *this;
  }
};

}

#endif
