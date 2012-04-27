//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//


#ifndef FAS_XTIME_TYPES_HPP
#define FAS_XTIME_TYPES_HPP

#include <climits>

#define FAS_NANOSEC  1000000000L
#define FAS_MICROSEC 1000000L
#define FAS_MILLISEC 1000L

#ifdef LLONG_MAX
  #if LLONG_MAX != 9223372036854775807
    #error
  #endif
#else
  #error
#endif


namespace fas
{
  typedef long long xsec_t;
}


#endif
