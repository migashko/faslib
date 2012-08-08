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
#if defined(HAVE_CLOCK_GETTIME_FUNC) && defined(FAS_USE_RT_LIB)

  timespec ts;
  if ( -1 == clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts) )
    return nanospan();
  return nanospan(ts.tv_sec, ts.tv_nsec);
#elif defined(HAVE_GETRUSAGE_FUNC)
  rusage ru;
  if ( 0 == getrusage(RUSAGE_SELF, &ru ) )
  {
    return microspan(ru.ru_utime.tv_sec, ru.ru_utime.tv_usec)+ 
           microspan(ru.ru_stime.tv_sec, ru.ru_stime.tv_usec);
  }
#endif
  return nanotime();

}

}

#endif
