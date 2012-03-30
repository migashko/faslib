// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ALIAS_HPP
#define FAS_AOP_ALIAS_HPP

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg>
struct del
{
  typedef metalist::del metatype;
  typedef Tg tag;
};

template<typename Tg, typename TTg>
struct alias
{
  typedef metalist::alias metatype;
  typedef Tg tag;
  typedef TTg target;
};

template<typename Tg, typename TTg>
struct forward
{
  typedef metalist::forward metatype;
  typedef Tg tag;
  typedef TTg target;
};

template<typename AL>
struct target
{
  typedef typename AL::target type;
};

template<typename Tg, typename TTg>
struct target< alias<Tg, TTg> >
{
  typedef TTg type;
};

template<typename Tg, typename TTg>
struct target< forward<Tg, TTg> >
{
  typedef TTg type;
};

}

#endif
