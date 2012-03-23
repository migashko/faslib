
#ifndef FAS_XTIME_NANOTIME_HPP
#define FAS_XTIME_NANOTIME_HPP

#include <fas/system/system.hpp>

#include <fas/xtime/nanospan.hpp>
#include <fas/xtime/types.hpp>


namespace fas
{

inline nanospan nanotime()
{

#if defined(HAVE_CLOCK_GETTIME_FUNC) && defined(FAS_USE_RT_LIB) && defined(FAS_USE_RT_LIB)
  timespec ts;
  if ( -1 == clock_gettime(CLOCK_MONOTONIC, &ts) )
    return nanospan();
  return nanospan(ts.tv_sec, ts.tv_nsec);
#elif defined(HAVE_GETTIMEOFDAY_FUNC)
  timeval tv;
  ::gettimeofday(&tv, 0);
  return nanospan(tv.tv_sec, tv.tv_usec*1000L);
#elif defined(HAVE__FTIME_S_FUNC)
  struct _timeb timebuffer; 
  _ftime_s( &timebuffer );
  return millispan(static_cast<long>(timebuffer.time), timebuffer.millitm);
#elif defined(HAVE__FTIME_FUNC)
  struct _timeb timebuffer; 
  _ftime( &timebuffer );
  return millispan(static_cast<long>(timebuffer.time), timebuffer.millitm);
#elif defined(HAVE_FTIME_FUNC)
	struct timeb timebuffer; 
	ftime( &timebuffer );
	return millispan(static_cast<long>(timebuffer.time), timebuffer.millitm);
#endif //HAVE_CLOCK_GETTIME_FUNC
  return nanospan(0, 0);

};


// CLOCK_PROCESS_CPUTIME_ID
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
  return nanospan(0, 0);

}


inline nanospan rate(const nanospan& s)
{
  return s == 0 ? nanospan::xmax : 1/s;
};


}

#endif
