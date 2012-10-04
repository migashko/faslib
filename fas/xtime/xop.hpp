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
  bool flag = f.xsec < s.xsec;
  return nanospan(
    f.sec - s.sec - flag,
    f.xsec - s.xsec + flag * FAS_NANOSEC
  );
}

inline nanospan operator + (const nanospan& f,  const nanospan& s)
{
  std::cout << "+sec1 " << f.sec << std::endl;
  std::cout << "+xsec1 " << f.xsec << std::endl;
  std::cout << "+sec2 " << s.sec << std::endl;
  std::cout << "+xsec2 " << s.xsec << std::endl;
  bool flag = (f.xsec + s.xsec >= FAS_NANOSEC);
  return nanospan(
    f.sec + s.sec + flag,
    f.xsec + s.xsec - flag * FAS_NANOSEC
  );
}

inline nanospan operator / (const nanospan& s, const nanospan& f)
{
  if ( f.xsec == 0)
  {
    xsec_t xsec = s.to_nanosec()/f.sec;
    return nanospan(
          static_cast< long > (xsec / FAS_NANOSEC ),
          static_cast< long > (xsec % FAS_NANOSEC )
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
    return nanospan(
          static_cast<long> ( xsec / FAS_NANOSEC ),
          static_cast<long> ( xsec % FAS_NANOSEC )
    );
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
