//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_XTIME_PROCESS_NANOTIME_HPP
#define FAS_XTIME_PROCESS_NANOTIME_HPP

#include <fas/system/system.hpp>
#include <fas/xtime/nanospan.hpp>
#include <fas/xtime/nanotime.hpp>
#include <fas/xtime/xop.hpp>
#include <fas/xtime/types.hpp>

namespace fas {

inline nanospan process_nanotime()
{
#if defined(HAVE_CLOCK_GETTIME_FUNC)
  timespec ts;
  if ( -1 == clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts) )
    return nanospan();
  return nanospan(ts.tv_sec, ts.tv_nsec);
#elif defined(HAVE_GETTIMEOFDAY_FUNC)
  timeval tv;
  ::gettimeofday(&tv, 0);
  return nanospan(tv.tv_sec, tv.tv_usec*1000L);
#elif defined(HAVE_GETRUSAGE_FUNC)
  rusage ru;
  if ( 0 == getrusage(RUSAGE_SELF, &ru ) )
  {
    return microspan(ru.ru_utime.tv_sec, ru.ru_utime.tv_usec)+ 
           microspan(ru.ru_stime.tv_sec, ru.ru_stime.tv_usec);
  }
#elif defined(HAVE_WINDOWS_H)
  __int64 wintime; 
  GetSystemTimeAsFileTime((FILETIME*)&wintime);
  wintime      -=116444736000000000i64;  //1jan1601 to 1jan1970
  return nanospan( static_cast<xsec_t>(wintime / 10000000i64), static_cast<xsec_t>(wintime % 10000000i64 *100) );
#endif

return nanotime();

}

}

#endif
