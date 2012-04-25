//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_TARGET_CAST_HPP
#define FAS_AOP_TARGET_CAST_HPP

#include <fas/aop/metalist.hpp>
#include <fas/aop/alias.hpp>
#include <fas/aop/forward.hpp>
#include <fas/aop/group.hpp>

namespace fas{

template<typename AL>
struct target_cast
{
  typedef typename AL::target type;
};

template<typename Tg, typename TgL>
struct target_cast< group<Tg, TgL> >
{
  typedef TgL type;
};

template<typename Tg, typename TTg>
struct target_cast< alias<Tg, TTg> >
{
  typedef TTg type;
};

template<typename Tg, typename TTg>
struct target_cast< forward<Tg, TTg> >
{
  typedef TTg type;
};

}

#endif
