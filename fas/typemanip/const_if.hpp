//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_CONST_IF_HPP
#define FAS_TYPEMANIP_CONST_IF_HPP

#include <fas/typemanip/const_if_c.hpp>

namespace fas{
  
template<typename T, typename C>
struct const_if
  : const_if_c<T, C::value>
{
};

}

#endif
