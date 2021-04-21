//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SYSTEM_SYSTEM_HPP
#define FAS_SYSTEM_SYSTEM_HPP


#include <fas/system/unp.hpp>

namespace fas{ namespace system{

inline int isatty(int fd)
{
#ifdef HAVE__ISATTY_FUNC
  return ::_isatty(fd);
#elif defined(HAVE_ISATTY_FUNC)
  return ::isatty(fd);
#else
  return 0;
#endif
}

inline bool is_atty_stdout()
{
#ifdef _POSIX_VERSION
  return isatty(fileno(stdout));
#elif defined WIN32
  return _isatty( _fileno( stdout ) )!=0;
#else
  return false;
#endif
}

inline bool is_atty_stderr()
{
#ifdef _POSIX_VERSION
  return isatty(fileno(stderr));
#else
  return false;
#endif
}


inline void sleep( time_t millisec )
{
#ifdef _POSIX_VERSION

#ifdef HAVE_USLEEP_FUNC
  ::usleep( static_cast<useconds_t>(millisec*1000) );
#else
  ::sleep(millisec/1000);
#endif

#elif defined(_WIN32)
  ::Sleep(static_cast<DWORD>(millisec));
#endif
}


}}

#endif
