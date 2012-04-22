//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_F_HPP
#define FAS_MP_F_HPP

#include <fas/integral/int_.hpp>

namespace fas{

template<typename T>
struct f
{
  enum { value = T::value };
  typedef int_< value > type;
};

}

#endif
