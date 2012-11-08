//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_HPP
#define FAS_AOP_ASPECT_HPP

#include <fas/aop/metalist.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/normalize.hpp>

namespace fas{

template<typename L = empty_list>
struct aspect
{
  typedef typename normalize<L>::type advice_list;
  typedef metalist::aspect metatype;
};

}

#endif
