//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_IF__HPP
#define FAS_TYPEMANIP_IF__HPP

#include <fas/typemanip/if_c.hpp>

namespace fas{

template<typename C, typename T1, typename T2>
struct if_
  : if_c<C::value, T1, T2>
{
};

}

#endif
