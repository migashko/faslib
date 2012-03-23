// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_SOME_TYPE_HPP
#define FAS_TYPEMANIP_SOME_TYPE_HPP

#include <fas/integral/bool_.hpp>

namespace fas{

template<typename L, typename R>
struct some_type
{
  enum { value = 0 };
  typedef bool_< value > type;
};

template<typename T>
struct some_type<T, T>
{
  enum { value = 1 };
  typedef bool_< value > type;
};

}

#endif
