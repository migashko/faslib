// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_IS_ADVICE_HPP
#define FAS_AOP_IS_ADVICE_HPP

#include <fas/aop/metalist.hpp>
#include <fas/aop/stub.hpp>
#include <fas/aop/advice.hpp>

#include <fas/typemanip/is_has_metatype.hpp>

namespace fas{

template<typename T>
struct is_advice
  : is_has_metatype<T, metalist::advice>
{
};


template<typename Tg, typename T>
struct is_advice< advice<Tg, T> >
{
  enum { value = 1};
  typedef true_ type;
};

template<typename Tg, typename R>
struct is_advice< stub<Tg, R> >
{
  enum { value = 1};
  typedef true_ type;
};


}

#endif
