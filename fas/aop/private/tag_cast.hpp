//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_TAG_CAST_HPP
#define FAS_AOP_TAG_CAST_HPP

#include <fas/typemanip/has_typename.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/type_advice.hpp>
#include <fas/aop/value_advice.hpp>
#include <fas/aop/alias.hpp>
#include <fas/aop/forward.hpp>
#include <fas/aop/remove_advice.hpp>
#include <fas/aop/group.hpp>
#include <fas/aop/tag.hpp>

namespace fas{

template<typename T>
struct tag_cast
{
  typedef typename T::tag type;
};

template<typename Tg, typename T>
struct tag_cast< advice<Tg, T> >
{
  typedef Tg type;
};

template<typename Tg, typename T>
struct tag_cast< type_advice<Tg, T> >
{
  typedef Tg type;
};

template<typename Tg, typename T>
struct tag_cast< value_advice<Tg, T> >
{
  typedef Tg type;
};

template<typename Tg>
struct tag_cast< remove_advice<Tg> >
{
  typedef Tg type;
};

template<typename Tg, typename TTg>
struct tag_cast< alias<Tg, TTg> >
{
  typedef Tg type;
};

template<typename Tg, typename TgL>
struct tag_cast< group<Tg, TgL> >
{
  typedef Tg type;
};

template<typename Tg>
struct tag_cast< tag<Tg> >
{
  typedef Tg type;
};

template<typename Tg, typename R>
struct tag_cast< stub<Tg, R> >
{
  typedef Tg type;
};


}

#endif
