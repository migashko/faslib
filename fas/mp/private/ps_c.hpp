//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_PS_C_HPP
#define FAS_MP_PS_C_HPP

#include <fas/mp/detail/ps.hpp>

namespace fas{

template<typename PH, typename PL, int DP = 0>
struct ps_c:
  detail::ps_impl<PH, PL, DP>
{
};
  

}

#endif
