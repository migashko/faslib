//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_XTIME_RATE_HPP
#define FAS_XTIME_RATE_HPP

#include <fas/xtime/nanospan.hpp>
#include <fas/xtime/xop.hpp>

namespace fas {

inline nanospan rate(const nanospan& s)
{
  return s == 0 ? nanospan::xmax : 1/s;
}

}

#endif
