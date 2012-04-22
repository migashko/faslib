//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_ANY_HPP
#define FAS_ALGORITHM_ANY_HPP

#include <fas/integral/bool_.hpp>

namespace fas{

template<typename>
struct any
{
  enum { value = 1 };
  typedef true_ type;
};

}

#endif
