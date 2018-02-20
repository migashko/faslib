//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_XTIME_XOP_HPP
#define FAS_XTIME_XOP_HPP

#include <fas/xtime/nanospan.hpp>

namespace fas {

inline nanospan operator - (const nanospan& f,  const nanospan& s)
{
  return f.xsec < s.xsec
         ? nanospan( f.sec - s.sec - 1, f.xsec - s.xsec + FAS_NANOSEC )
         : nanospan( f.sec - s.sec, f.xsec - s.xsec);
}

inline nanospan operator + (const nanospan& f,  const nanospan& s)
{
  return f.xsec + s.xsec >= FAS_NANOSEC
        ? nanospan( f.sec + s.sec + 1, f.xsec + s.xsec - FAS_NANOSEC )
        : nanospan( f.sec + s.sec, f.xsec + s.xsec );
}

inline nanospan operator / (const nanospan& s, const nanospan& f)
{
  if ( f.xsec == 0)
  {
    xsec_t xsec = s.to_nanosec()/f.sec;
    return nanospan(
          static_cast< xsec_t > (xsec / FAS_NANOSEC ),
          static_cast< xsec_t > (xsec % FAS_NANOSEC )
    );
  }
  else
    return nanospan( s.to_double() / f.to_double() );
}

inline nanospan operator * (const nanospan& s, const nanospan& f)
{
  if ( f.xsec == 0)
  {
    xsec_t xsec = s.to_nanosec()*f.sec;
    if ( xsec != 0L)
      return nanospan(
        static_cast<xsec_t> ( xsec / FAS_NANOSEC ),
        static_cast<xsec_t> ( xsec % FAS_NANOSEC )
      );
    else
      return nanospan(0, 0);
  }
  else
    return nanospan( s.to_double() * f.to_double() );
}

inline bool operator == (const nanospan& f,  const nanospan& s)
{
  return f.sec == s.sec && f.xsec == s.xsec;
}

inline bool operator != (const nanospan& f,  const nanospan& s)
{
  return !(f == s);
}

inline bool operator < (const nanospan& f,  const nanospan& s)
{
  if ( f.sec < s.sec ) return true;
  return f.sec == s.sec ? f.xsec < s.xsec : false;
}

inline bool operator > (const nanospan& f,  const nanospan& s)
{
  if ( f.sec > s.sec ) return true;
  return f.sec == s.sec ? f.xsec > s.xsec : false;
}

inline bool operator <= (const nanospan& f,  const nanospan& s)
{
  return !( f > s );
}

inline bool operator >= (const nanospan& f,  const nanospan& s)
{
  return !( f < s );
}

}

#endif
