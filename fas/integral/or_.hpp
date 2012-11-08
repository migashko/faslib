//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_OR__HPP
#define FAS_INTEGRAL_OR__HPP

#include <fas/integral/bool_.hpp>

namespace fas{

template<typename A, typename B>
struct or_
  : or_< bool_< A::value!=0 >, B >
{
};

template<typename B>
struct or_<true_, B>
{
  enum { value = 1 };
  typedef true_ type;
};

template<typename B>
struct or_<false_, B>
{
  enum { value = (B::value!=0) };
  typedef bool_< value > type;
};

}

#endif
