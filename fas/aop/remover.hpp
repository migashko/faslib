//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_REMOVER_HPP
#define FAS_AOP_REMOVER_HPP

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg>
struct remover
{
  typedef metalist::remover metatype;
  typedef Tg tag;
};

}

#endif
