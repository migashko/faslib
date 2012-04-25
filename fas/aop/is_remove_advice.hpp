//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_IS_REMOVE_ADVICE_HPP
#define FAS_AOP_IS_REMOVE_ADVICE_HPP

#include <fas/aop/metalist.hpp>
#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/aop/remove_advice.hpp>
#include <fas/integral/bool_.hpp>

namespace fas{

template<typename T>
struct is_remove_advice
{
  enum { value = is_has_metatype<T, metalist::remove_advice>::value };
  typedef bool_< value > type;
};

template<typename Tg>
struct is_remove_advice< remove_advice<Tg> >
{
  enum { value = 1};
  typedef true_ type;
};


}

#endif
