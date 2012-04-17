// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_PS_C_HPP
#define FAS_MP_PS_C_HPP

#include "detail/ps.hpp"

namespace fas{

template<typename PH, typename PL, int DP = 0>
struct ps_c:
  detail::ps_helper<PH, PL, DP>
{
  // typedef typename detail::ps_helper<PH, PL, DP>::type type;
};
  

}

#endif
