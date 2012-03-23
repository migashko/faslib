// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_IS_GROUP_HPP
#define FAS_AOP_IS_GROUP_HPP

#include <fas/aop/metalist.hpp>
#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/aop/group.hpp>

namespace fas{

template<typename T>
struct is_group
  : is_has_metatype<T, metalist::group>
{
};


template<typename Tg, typename TgL>
struct is_group< group<Tg, TgL> >
{
  enum { value = 1};
  typedef true_ type;
};



}

#endif
