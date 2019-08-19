//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_XTIME_XSPAN_HPP
#define FAS_XTIME_XSPAN_HPP

#include <fas/xtime/types.hpp>
#include <fas/utility/useless_cast.hpp>

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

  template<xsec_t X>
  xspan<I>& operator=(const xspan<X>& span )
  {
    sec = span.sec;
    xsec = convert<xspan<X>::xmax>(span.xsec);
    return *this;
  }

  xspan(xsec_t s, xsec_t xs)
    : sec(s)
    , xsec(xs)
  {}

  explicit xspan(short s)
    : sec(useless_cast<xsec_t>(s))
    , xsec(0)
  {}

  explicit xspan(unsigned short s)
    : sec(useless_cast<xsec_t>(s))
    , xsec(0)
  {}

  explicit xspan(int s)
    : sec(useless_cast<xsec_t>(s))
    , xsec(0)
  {}

  explicit xspan(unsigned int s)
    : sec(useless_cast<xsec_t>(s))
    , xsec(0)
  {}

  explicit xspan(long s)
    : sec(useless_cast<xsec_t>(s))
    , xsec(0)
  {}

  explicit xspan(unsigned long s)
    : sec(useless_cast<xsec_t>(s))
    , xsec(0)
  {}

  explicit xspan(float s)
    : sec( useless_cast<xsec_t>(s) )
    , xsec( useless_cast<xsec_t>( (s - sec)*xmax ) )
  {}

  explicit xspan(double s)
    : sec( useless_cast<xsec_t>(s) )
    , xsec( useless_cast<xsec_t>( (s - useless_cast<double>(sec) )*xmax  ) )
  {}

  xsec_t to_nanosec() const
  {
    return ( useless_cast<xsec_t>(sec) * xmax + xsec) * (FAS_NANOSEC/xmax );
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
    return useless_cast<float>( to_nanosec() ) / xmax;
  }

  double to_double() const
  {
    return useless_cast<double>( to_nanosec() ) / xmax;
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
      return useless_cast<xsec_t>( useless_cast<double>(xsec * M) / useless_cast<double>(F) );
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
