//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_AND__HPP
#define FAS_INTEGRAL_AND__HPP

#include <fas/integral/bool_.hpp>

namespace fas{

template<typename A, typename B>
struct and_
{
  enum { value = A::value && B::value };
  typedef bool_< value > type;
};

}

#endif
