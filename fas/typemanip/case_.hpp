//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_CASE__HPP
#define FAS_TYPEMANIP_CASE__HPP

#include <fas/typemanip/case_c.hpp>

namespace fas{

template<typename C, typename T>
struct case_
  : case_c<C::value, T>
{
};

}

#endif
