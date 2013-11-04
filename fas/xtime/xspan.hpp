//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_XTIME_XSPAN_HPP
#define FAS_XTIME_XSPAN_HPP

#include <fas/xtime/types.hpp>

namespace fas {

template<xsec_t T, xsec_t F>
struct xconverter;

template<xsec_t I>
struct xspan
{
  static const xsec_t xmax = I;

  xsec_t sec;

  xsec_t xsec;

  xspan()
    : sec(0)
    , xsec(0)
  {}

  template<xsec_t X>
  xspan(const xspan<X>& span )
    : sec(span.sec)
    , xsec( convert<xspan<X>::xmax>(span.xsec))
  {}

  xspan(xsec_t sec, xsec_t xsec)
    : sec(sec)
    , xsec(xsec)
  {}

  xspan(short sec)
    : sec(static_cast<xsec_t>(sec))
    , xsec(0)
  {}

  xspan(unsigned short sec)
    : sec(static_cast<xsec_t>(sec))
    , xsec(0)
  {}

  xspan(int sec)
    : sec(static_cast<xsec_t>(sec))
    , xsec(0)
  {}

  xspan(unsigned int sec)
    : sec(static_cast<xsec_t>(sec))
    , xsec(0)
  {}

  xspan(long sec)
    : sec(static_cast<xsec_t>(sec))
    , xsec(0)
  {}

  xspan(unsigned long sec)
    : sec(static_cast<xsec_t>(sec))
    , xsec(0)
  {}

  xspan(float s)
    : sec( static_cast<xsec_t>(s) )
    , xsec( static_cast<xsec_t>( (s - sec)*xmax ) )
  {}

  xspan(double s)
    : sec( static_cast<xsec_t>(s) )
    , xsec( static_cast<xsec_t>( (s - sec)*xmax  ) )
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

  template<xsec_t X>
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

  template<xsec_t X>
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

  template<xsec_t X>
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

  template<xsec_t X>
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

  template<xsec_t F>
  static xsec_t convert(xsec_t xsec)
  {
    return xconverter< I,  F>::convert(xsec);
  }
};

namespace detail
{

  template<xsec_t M, xsec_t F, int Less>
  struct xconverter
  {
    static xsec_t convert(xsec_t xsec)
    {
      return (xsec * M) / F;
    }
  };

  template<xsec_t M, xsec_t F>
  struct xconverter<M, F, false>
  {
    static xsec_t convert(xsec_t xsec)
    {
      return xsec * (M / F);
    }
  };
}

template<xsec_t T, xsec_t F>
struct xconverter
  : detail::xconverter<T, F, (T < F ) >
{

};


}

#endif
