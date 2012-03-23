// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_HAS_TAG_HPP
#define FAS_AOP_HAS_TAG_HPP

#include <fas/typemanip/has_typename.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/alias.hpp>

namespace fas{

FAS_HAS_TYPENAME(has_tag, tag);

template<typename T>
struct get_tag
{
  typedef typename T::tag type;
};

template<typename Tg, typename T>
struct get_tag< advice<Tg, T> >
{
  typedef Tg type;
};

template<typename Tg>
struct get_tag< del<Tg> >
{
  typedef Tg type;
};

}

#endif
