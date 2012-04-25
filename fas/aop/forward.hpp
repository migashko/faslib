//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_FORWARD_HPP
#define FAS_AOP_FORWARD_HPP

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg, typename TTg>
struct forward
{
  typedef metalist::forward metatype;
  typedef Tg tag;
  typedef TTg target;
};

}

#endif
