//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_PS_HPP
#define FAS_MP_PS_HPP

#include <fas/mp/private/ps_c.hpp>
#include <fas/integral/int_.hpp>

namespace fas{

template<typename PH, typename PL, typename DP = int_<0> >
struct ps:
  ps_c<PH, PL, DP::value>
{
};
 

}

#endif
