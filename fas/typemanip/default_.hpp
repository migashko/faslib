//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_DEFAULT__HPP
#define FAS_TYPEMANIP_DEFAULT__HPP

#include <fas/typemanip/case_c.hpp>

namespace fas{

template<typename T>
struct default_
{
  enum { value = 1 };
  typedef T type;
};

}

#endif
